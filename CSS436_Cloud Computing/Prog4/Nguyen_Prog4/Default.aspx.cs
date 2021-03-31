/* Jessica Nguyen
 * CSS436, Prog4
 * Default.aspx.cs
 * This program uses multiple services in the cloud working together. In particular I will use Blob Storage, Azure Tables,
 * and website technology which allows server side code ASP.Net to perform queries on user inputs.
*/
using System;
using System.Web.UI;
using Azure.Storage.Blobs.Specialized;
using Microsoft.Extensions.Configuration;
using System.IO;
using Microsoft.Azure.Cosmos.Table;
using Azure.Storage.Blobs;
using System.Web.UI.WebControls;
using System.Threading;
using System.Net.Http;
using System.Net;
using System.Collections.Generic;
using System.Linq;

namespace WebApplication1
{
    /* This is a class representing a Person as an Azure TableEntity for adding into Azure Table on the cloud
     * Each Person has a string fname, string lname, and string attributes parsed from text input
     */
    public class Person : TableEntity
    {
        public Person() { }
        public Person(string lname, string fname)
        {
            PartitionKey = fname;
            RowKey = lname;
            DataItems = new Dictionary<string, string>();
            //DataItems.Add("foo", "bar");
            //DataItems.Add("Jacob", "Xander");
        }
        public void Add(string key, string value)
        {
            DataItems.Add(key, value);
        }
        public Dictionary<string, string> DataItems { get; set; }

        public override IDictionary<string, EntityProperty> WriteEntity(OperationContext operationContext)
        {
            var results = base.WriteEntity(operationContext);
            foreach (var item in DataItems)
            {
                results.Add("D_" + item.Key, new EntityProperty(item.Value));
            }
            return results;
        }

        public override void ReadEntity(IDictionary<string, EntityProperty> properties, OperationContext operationContext)
        {
            DataItems = new Dictionary<string, string>();

            foreach (var item in properties)
            {
                if (item.Key == "Timestamp")
                {
                    Timestamp = item.Value.DateTimeOffsetValue.Value;
                }
                else if (item.Key == "RowKey")
                {
                    RowKey = item.Value.StringValue;
                }
                else if (item.Key == "PartitionKey")
                {
                    PartitionKey = item.Value.StringValue;
                }
                else if (item.Key.StartsWith("D_"))
                {
                    string realKey = item.Key.Substring(2);
                    DataItems[realKey] = item.Value.StringValue;
                }
            }
        }
    }

    public partial class _Default : Page
    {
        //sets up the credentials without hard-coding into the cs file
        static IConfigurationRoot GetConfiguration()
            => new ConfigurationBuilder()
            .SetBasePath(Directory.GetParent(AppContext.BaseDirectory).FullName)
            .AddJsonFile("appsettings.json")
            .Build();

        //constants used in this program to connect to cloud services: Blob and Table
        private static readonly string url = "https://css490.blob.core.windows.net/lab4/input.txt";
        private static IConfigurationRoot config = GetConfiguration();
        private static BlobBaseClient containerClient;
        private static CloudTable tableClient;
        private static Boolean connectTable = false;
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        //LOAD BUTTON
        /*
         * precondition: All credentials are properly set up
         * postcondition: program will load input Blob object into my own Blob Storage, 
         *                parse the Blob text file and add the list of people in the text as key/value attributes in my own Azure Table instance
         */
        protected void Button1_Click(object sender, EventArgs e)
        {
            Load();

        }

        private void Load()
        {
            CopyBlob();

            CreateTable();

            Deserialize();

            connectTable = true;

        }
        /* CopyBlob -- copies predetermined input Blob into my own Blob Storage account
         * precondition: input Blob URL is valid and public
         * postcondition: Azure Blob Storage copies a separate Blob instance into my account
         *                If the original Blob text file is changed, the Blob instance will be updated accordinglys
         */
        private void CopyBlob()
        {
            try
            {
                Label2.Text = "";
                ConnectToBlob();

                Uri path = new Uri(url);

                // Create a 'HttpWebRequest' object for the specified url.
                HttpWebRequest myHttpWebRequest = (HttpWebRequest)WebRequest.Create(url);
                // Send the request and wait for response.
                HttpWebResponse myHttpWebResponse = (HttpWebResponse)myHttpWebRequest.GetResponse();


                if (myHttpWebResponse.StatusCode == HttpStatusCode.OK)
                {
                    Label1.Text = myHttpWebResponse.StatusDescription;
                    containerClient.StartCopyFromUri(path);
                    myHttpWebResponse.Close();
                }
                else
                {
                    Label2.Text = "ERROR: URL TO BLOB DOESN'T EXIST/ISN'T A VALID LINK";
                }


            }
            catch (Exception e)
            {
                Label2.Text = "ERROR: Invalid input text link. " + e.Message;
            }

        }

        /* ConnectToBlob -- instantiate a BlobBaseClient object to interact with Azure Blob Storage Service
         * precondition: credentials are set up in appsetting.json
         */
        private void ConnectToBlob()
        {
            try
            {
                Label2.Text = "";
                containerClient = new BlobBaseClient(config["AzureStorage:ConnectionString"], config["AzureStorage:Container"], config["AzureStorage:Blob"]);
            }
            catch (Exception e)
            {
                Label2.Text = "ERROR: " + e.Message;
            }

        }

        /* ConnectToTable --  instantiate a CloudTableClient object to interact with Azure Table Service
         * precondition: credentials are set up in appsetting.json
         */
        private void ConnectToTable()
        {
            try
            {
                Label2.Text = "";
                var storageAccount = Microsoft.Azure.Cosmos.Table.CloudStorageAccount.Parse(config["AzureTable:ConnectionString"]);

                var _tableClient = storageAccount.CreateCloudTableClient();

                tableClient = _tableClient.GetTableReference("input");
            }
            catch (Exception e)
            {
                Label2.Text = "ERROR: " + e.Message;
            }
        }

        private static int retries = 3; //3 retries max
        private static int time = (int)TimeSpan.FromSeconds(20).TotalMilliseconds; //everytime sleep is 30 secs

        /* CreateTable -- create a table instance on my Azure Table account
         */
        private void CreateTable()
        {
            try
            {
                Label2.Text = "";
                ConnectToTable();

                if (!tableClient.Exists())
                {
                    tableClient.CreateIfNotExists();
                }

                retries = 3;
                time = (int)TimeSpan.FromSeconds(20).TotalMilliseconds;
            }
            catch (Exception e)
            {
                if (retries == 0)
                {
                    Label2.Text = "ERROR: " + e.Message;

                }
                else
                {
                    retries--;
                    Thread.Sleep(time);
                    time *= 2; //double the sleep time after every retry
                    Load(); //call Load again after sleep
                }
            }
        }

        //CLEAR BUTTON
        /* NOTE: AFTER PRESSING CLEAR BUTTON, WAIT AT LEAST 30 SECONDS BEFORE CLICKING ON LOAD BUTTON -- AZURE TAKES TIME TO DELETE THE TABLE
         * postcondition: deletes my Blob file on Blob Storage;
         *                deletes my whole Table with all key/value pairs on Azure Table;
         *                clears out the text input boxes in the html file
         */
        protected void Button2_Click1(object sender, EventArgs e)
        {
            try
            {
                //CLEAR ENTITIES IN TABLE
                ConnectToTable();
                var entities = tableClient.ExecuteQuery(new TableQuery<Person>()).ToList();
                foreach (var item in entities)
                {
                    TableQuery<Person> deleteQuery = new TableQuery<Person>().Where(TableQuery.CombineFilters(
                    TableQuery.GenerateFilterCondition("PartitionKey", QueryComparisons.Equal, item.PartitionKey),
                    TableOperators.And,
                    TableQuery.GenerateFilterCondition("RowKey", QueryComparisons.Equal, item.RowKey))
                    );
                    //System.Diagnostics.Debug.WriteLine("key: " + item.Key + ", value: " + item.Value);
                    var tableQueryResult = tableClient.ExecuteQuerySegmented(deleteQuery, null);
                    List<Person> entity = tableQueryResult.Results;
                    foreach (Person p in entity)
                    {
                        TableBatchOperation tableBatchOperation = new TableBatchOperation();
                        tableBatchOperation.Add(TableOperation.Delete(p));
                        tableClient.ExecuteBatch(tableBatchOperation);
                    }

                }

                //CLEAR BLOB
                ConnectToBlob();
                ConnectToBlob();
                containerClient.DeleteIfExists();

                //clear textboxes
                TextBox1.Text = "";
                TextBox2.Text = "";
                Label2.Text = "";
                Label3.Text = "";

                Label1.Text = "SUCCESFULLY CLEARED FROM BLOB STORAGE AND AZURE TABLE";
            }
            catch (Exception ex)
            {
                Label2.Text = "ERROR: " + ex.Message;
            }
        }

        /* Deserialize -- parses the input text file and separate out first name, last name, and attributes and add them to Azure Table
         * precondition: credentials are set up in appsetting.json
         */
        private void Deserialize()
        {
            try
            {
                Label2.Text = "";
                // Create the container and return a container client object
                BlobContainerClient containerClient = new BlobContainerClient(config["AzureStorage:ConnectionString"], config["AzureStorage:Container"]);
                // Get a reference to a blob
                BlobClient blobClient = containerClient.GetBlobClient("input.txt");

                //Download the blob's contents 

                if (blobClient.Exists())
                {
                    var response = blobClient.Download();
                    using (var streamReader = new StreamReader(response.Value.Content))
                    {


                        while (!streamReader.EndOfStream)
                        {
                            var line = streamReader.ReadLine();
                            if (line == null)
                            {
                                Label1.Text = "BLOB TEXT CONTENT IS EMPTY!";
                                return;
                            }
                            //string line;

                            //// Read the file and display it line by line.  
                            //System.IO.StreamReader file = new System.IO.StreamReader("C:\\Users\\Khanh Nguyen\\Downloads\\input.txt");
                            //string text = file.ToString();

                            //while ((line = file.ReadLine()) != null)
                            //{
                            /* 1. empty - X
                             * 2. only 1 element - X
                             * 3. at least 2 elements - ok
                             * 4. only fname then attributes - X can check if the second one includes equal sign
                             * 5. only lname then attributes - X can check if the second one includes equal sign
                             * 6. only fname, lname, nothing else - ok
                             * 7. everything else - ok
                             */

                            string[] ssize = line.Split(new char[0], StringSplitOptions.RemoveEmptyEntries); //split line by whitespace
                            if (ssize.Length == 0 || ssize.Length < 2 || ssize[0].Contains("=") || ssize[1].Contains("="))
                            { //make sure the first 2 items must be of form firstname, lastname; if not, ignore
                                continue;
                            }
                            else
                            {
                                Person p = new Person(Format(ssize[0]), Format(ssize[1]));

                                if (ssize.Length >= 3)
                                {

                                    for (int i = 2; i < ssize.Length; i++)
                                    {
                                        string attr = ssize[i];
                                        string[] individualAttributes = attr.Split('=');
                                        if (individualAttributes.Length > 1)
                                        {
                                            p.Add(Format(individualAttributes[0]), Format(individualAttributes[1]));
                                        }
                                    }

                                }
                                //add person to table
                                if (!AddToTable(p))
                                {
                                    //HOW TO WRITE TO A DISPLAY ON THE WEBSITE?
                                    Console.WriteLine("Unable to insert Person " + p.ToString());
                                }
                            }
                        }//END WHILE 
                    } //END USING

                } //END IF
                Label1.Text = "LOADING COMPLETE!";
            }


            catch (Exception e)
            {
                Label2.Text = "ERROR: " + e.Message;
            }
        }

        /* AddToTable -- helper method to add Person object to Azure Table
         * precondition: Person input is not null object
         * postcondition:  if the fname and lname are same, table will override the old value and update with the one thats added the latest;
         *                 return false if Person object passed in is null
         */
        private Boolean AddToTable(Person p)
        {
            try
            {
                Label2.Text = "";
                if (p == null) { return false; }

                var batch = new TableBatchOperation();
                batch.InsertOrReplace(p); //stage insert
                tableClient.ExecuteBatch(batch); //commit insert
            }
            catch (Exception e)
            {
                Label2.Text = "ERROR: " + e.Message;
            }
            return true;
        }

        //QUERY BUTTON
        /*
         * precondition: returns on the output with matches of the user input in the Table database
         * postcondition: if user enters in only first name, all objects with matching first name keys will be displayed;
         *                if user enters in only last name, all objects matching last name keys will be displayed;
         *                if user enters in both first and last name, one key/value object matching both will be displayed
         */
        protected void Button3_Click1(object sender, EventArgs e)
        {
            try
            {
                Label2.Text = "";
                Label3.Text = "";
                if (!connectTable)
                {
                    Load();
                }

                string fname = Format(TextBox1.Text);
                string lname = Format(TextBox2.Text);

                System.Collections.Generic.IEnumerable<Person> itemlist = null;

                if (!string.IsNullOrWhiteSpace(fname) && !string.IsNullOrWhiteSpace(lname)) //if both
                {

                    TableQuery<Person> CustomerQuery = new TableQuery<Person>().Where(TableQuery.CombineFilters(
                    TableQuery.GenerateFilterCondition("PartitionKey", QueryComparisons.Equal, fname),
                    TableOperators.And,
                    TableQuery.GenerateFilterCondition("RowKey", QueryComparisons.Equal, lname))
                    );
                    itemlist = tableClient.ExecuteQuery(CustomerQuery);

                }
                else if (!string.IsNullOrWhiteSpace(fname) && string.IsNullOrWhiteSpace(lname)) //if first name only
                {
                    TableQuery<Person> CustomerQuery = new TableQuery<Person>().Where(
                    TableQuery.GenerateFilterCondition("PartitionKey", QueryComparisons.Equal, fname
                    ));
                    itemlist = tableClient.ExecuteQuery(CustomerQuery);

                }
                else if (string.IsNullOrWhiteSpace(fname) && !string.IsNullOrWhiteSpace(lname)) //if last name only
                {
                    TableQuery<Person> CustomerQuery = new TableQuery<Person>().Where(
                   TableQuery.GenerateFilterCondition("RowKey", QueryComparisons.Equal, lname
                   ));
                    itemlist = tableClient.ExecuteQuery(CustomerQuery);

                }

                if (itemlist != null)
                {


                    foreach (Person res in itemlist)
                    {
                        string answer = "";
                        answer += "First Name: " + res.PartitionKey + ", ";
                        answer += "Last Name: " + res.RowKey;

                        foreach (var attribute in res.DataItems)
                        {
                            answer += ", " + attribute.Key + ": " + attribute.Value;
                        }

                        Label3.Text += answer + "<br /><br />";
                    }


                    itemlist = null;

                }
            }
            catch (Exception ex)
            {
                Label2.Text = "ERROR: " + ex.Message;
            }
        }

        /* Format -- formats all input text to capitalize only the first letter of input string 
         
         * postcondition: returns empty string if input is null or only whitespace
         */
        private static string Format(string s)
        {
            if (string.IsNullOrWhiteSpace(s))
            {
                return "";
            }
            s = s.ToLower();
            s = s[0].ToString().ToUpper() + s.Substring(1);
            return s;
        }

        protected void TextBox1_TextChanged(object sender, EventArgs e)
        {
            //fname

        }

        protected void TextBox2_TextChanged(object sender, EventArgs e)
        {
            //lname
        }

        protected void TextBox3_TextChanged(object sender, EventArgs e)
        {
            //result
        }

        static void ErrorTextBox_TextChanged(object sender, EventArgs e)
        {
            //result
        }


    }


}