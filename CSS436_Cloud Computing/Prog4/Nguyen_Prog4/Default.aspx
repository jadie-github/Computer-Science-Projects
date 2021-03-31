<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication1._Default" %>


<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <!-- partial:index.partial.html -->
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css2?family=Comfortaa:wght@300&display=swap" rel="stylesheet">



    <div class="intro">
        <h1>Jessica Nguyen</h1>
        <p>CSS 436 - Program 4</p>
        <p>
            This program uses multiple services in the cloud working together. In particular I will use Blob Storage, Azure Tables, and website technology which allows server side code ASP.Net to perform queries on user inputs.
        </p>
        &nbsp;&nbsp;
    </div>

    <div class="text-center">

        <asp:UpdatePanel ID="panel1" runat="server">
            <ContentTemplate>
                <div class="buttons">
                    <asp:Button class="bu" ID="Button1" runat="server" OnClick="Button1_Click" Text="LOAD" />
                    <asp:Button class="bu" ID="Button2" runat="server" OnClick="Button2_Click1" Text="CLEAR" />
                </div>
                <br>
                <br>


                <asp:Label class="bold" ID="Label1" runat="server" Text=""></asp:Label>
                <br />
                <asp:Label class="error bold" ID="Label2" runat="server" Text=""></asp:Label>
                <br>
                <br>
                <div class="names">
                    <div class="card flex-item">
                        <asp:TextBox ID="TextBox1" runat="server" OnTextChanged="TextBox1_TextChanged" class="a form-control mr-sm-2" type="username" placeholder="First Name" aria-label="Username"></asp:TextBox>
                    </div>
                    <!--end box 1-->

                    <div class="card flex-item">
                        <asp:TextBox ID="TextBox2" runat="server" OnTextChanged="TextBox2_TextChanged" class="a form-control mr-sm-2" type="username" placeholder="Last Name" aria-label="Username"></asp:TextBox>
                    </div>
                    <!--end box 2-->

                </div>
                <br>
                <div class="buttons">
                    <asp:Button ID="Button3" runat="server" OnClick="Button3_Click1" Text="QUERY" />
                </div>

                <br>
                <br>

                <p class="bold">
                    RESULTS
                </p>
                <div class="result">
                    <asp:Label ID="Label3" runat="server" Text=""></asp:Label>
                </div>
                <%--<div class="table">

                    <asp:Table ID="myTable" runat="server" Width="100%">
                        <asp:TableHeaderRow>
                            <asp:TableCell class="bold">First Name</asp:TableCell>
                            <asp:TableCell class="bold">Last Name</asp:TableCell>
                        </asp:TableHeaderRow>
                    </asp:Table>
                </div>--%>
            </ContentTemplate>

        </asp:UpdatePanel>

        <asp:UpdateProgress ID="ppp1" runat="server" AssociatedUpdatePanelID="panel1">
            <ProgressTemplate>
                <div id="overlay">
                    <div id="modalprogress">
                        <img id="indicator" src="loading.gif" />
                    </div>
                </div>
            </ProgressTemplate>
        </asp:UpdateProgress>
        <script src='https://cdn.jsdelivr.net/npm/bootstrap@4.6.0/dist/js/bootstrap.bundle.min.js'></script>
    </div>
</asp:Content>
