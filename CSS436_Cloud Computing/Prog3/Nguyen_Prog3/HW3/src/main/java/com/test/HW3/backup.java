/* Jessica Nguyen
 * CSS436, Prog3
 * App.java
 * This program recursively traverses the files of a directory and makes a backup to
the cloud. 
 * */

package com.test.HW3;

import java.io.*;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

import com.amazonaws.services.s3.AmazonS3;
import com.amazonaws.services.s3.AmazonS3ClientBuilder;
import com.amazonaws.services.s3.model.*;
import com.amazonaws.AmazonClientException;
import com.amazonaws.AmazonServiceException;
import com.amazonaws.services.s3.transfer.MultipleFileUpload;
import com.amazonaws.services.s3.transfer.TransferManagerBuilder;
import com.amazonaws.services.s3.transfer.TransferManager;

public class backup {

	/*
	 * 1: backup/restore 2: backup - local dir ; restore - cloud dir 3: backup -
	 * cloud dir ; restore - local dir
	 */
	public static void main(String[] args) {
		if (args.length != 2) {
			System.err.println(
					"ERROR: Incorrect parameters\n" + "Parameters must be in the form: backup <source>::<destination>");
			return;
		}

		final AmazonS3 user = AmazonS3ClientBuilder.defaultClient();

		backUp(user, args[0], args[1]);
	}

	/*
	 * backUp() -- backup files specified in the local directory dirPath and uploads
	 * it to the S3 bucket “name” of the AWS User “s3Client” Preconditions: dirPath
	 * and name are initialized String objects, s3Client exists in AWS with
	 * credentials set up in your environment Postconditions: returns ERROR if the
	 * input name isn’t in the form bucket::directory. Create a new bucket named
	 * “name” if the input user doesn’t have that bucket in S3. The new bucket name
	 * will be input “name” plus the current timestamp in milliseconds. Returns
	 * without running the backup algorithm if there are no changes locally to be
	 * uploaded onto cloud to save bandwidth. Succesfully upload new files onto
	 * cloud if there are new changes locally.
	 * 
	 */
	private static void backUp(AmazonS3 s3Client, String dirPath, String name) {
		if (!name.contains("::")) {
			System.out.println("ERROR: Input bucket must be formatted in the form \"bucketname::directoryName\" only");
			return;
		}
		File file = new File(dirPath);
		if (!file.exists()) {
			System.out.println("ERROR: Input local directory " + dirPath + " doesn't exist. Please try again.");
			return;
		}
		
		String[] split = name.split("::");
		
		if(split.length < 2) {
			System.out.println("ERROR: Empty String detected for bucket and directory strings. Please enter at least 1 character for each");
			return;
		}
		
		if(name.split("::")[0].isEmpty()) {
			System.out.println("ERROR: Input bucket is an empty String. Please enter at least 1 character");
			return;
		}
		if(name.split("::")[1].isEmpty()) {
			System.out.println("ERROR: Input cloud directory is an empty String. Please enter at least 1 character");
			return;
		}
		
		String bucket = split[0];
		String cloudDirectory = split[1];

		// assuming that if the bucket doesn't exist we will have to create one and then
		// upload the local directory there
		if (!bucketExists(s3Client, bucket)) {
			try {
				bucket += System.currentTimeMillis();
				System.out.println("Initializing new bucket " + bucket);
				s3Client.createBucket(bucket);
			} catch (AmazonS3Exception e) {
				System.err.println(e.getErrorMessage());
				System.exit(1);
			}
		}

		if (compare(s3Client, dirPath, bucket, cloudDirectory)) {
			System.out.println("The input local directory " + dirPath
					+ " has not been modified locally since it was backed up.\nNo need to move data again.\n"
					+ "No changes made to S3 directory " + name);
			return;
		}

		// upload from local to existing bucket
		TransferManager mgr = TransferManagerBuilder.standard().build();
		try {
			System.out.println("Path name of input directory is " + dirPath + "\n");
			File folder = new File(dirPath);
			if (!folder.exists()) {
				System.out.println("The input directory path does not exist. Please try again.");
				return;
			}

			System.out.println("Backing up to bucket " + bucket + " in directory " + cloudDirectory + "...\n");
			MultipleFileUpload files = mgr.uploadDirectory(bucket, cloudDirectory, folder, true);
			files.isDone();
			files.waitForCompletion();

			System.out.println("Back up to cloud directory Completed");

		} catch (AmazonServiceException e) {
			System.err.println(e.getErrorMessage());
			System.exit(1);
		} catch (AmazonClientException e) {
			System.err.println("Amazon client error: " + e.getMessage());
			System.exit(1);
		} catch (InterruptedException e) {
			System.err.println("Transfer interrupted: " + e.getMessage());
			System.exit(1);
		}
		mgr.shutdownNow();
	}

	/*
	 * bucketExists() -- checks if the bucket “name” exists on S3 for the input AWS
	 * user “user” Preconditions: name is an initialized String object, user exists
	 * in AWS with credentials set up in your environment Postconditions: return
	 * true if bucket exists Return false if bucket doesn’t exist
	 */
	private static boolean bucketExists(AmazonS3 user, String name) {

		List<Bucket> buckets = user.listBuckets();
		for (Bucket b : buckets) {

			if (b.getName().equals(name)) {
				return true;
			}
		}
		System.out.println("Bucket " + name + " doesn't exist in client's S3.");
		return false;
	}

	/*
	 * compare() -- recursively compare if the local directory “localPath” has the
	 * same structure and file timestamps as the cloud bucket “bucket” does
	 * Preconditions: localPath, bucket and key are initialized String objects, user
	 * exists in AWS with credentials set up in your environment Postconditions:
	 * returns false if the cloud doesn’t have a file that exists locally in given
	 * directory “localPath”. Returns false if the timestamp of the local file is
	 * later than the cloud’s timestamp (meaning it has been modified locally but
	 * not yet reflected onto the cloud). Returns true otherwise.
	 */
	public static boolean compare(AmazonS3 user, String localPath, String bucket, String key) {
		File loc = new File(localPath);
		File[] filesInFolder = loc.listFiles();

		List<File> sub = new ArrayList<>();
		for (File f : filesInFolder) {
			if (!f.isDirectory()) {
				String fileName = key + "/" + f.getName();

				if (!user.doesObjectExist(bucket, fileName)) { // if the cloud doesn't have this file then return false,
																// we need to update cloud
					return false;
				} else {
					Date localLastModified = new Date(loc.lastModified());
					Date cloudLastModified = user.getObject(bucket, fileName).getObjectMetadata().getLastModified();
					if (localLastModified.after(cloudLastModified)) { // file has been modified locally, we need to
																		// update cloud
						return false;
					}
				}
			} else {
				sub.add(f);
			}
		}
		for (File f : sub) { // checking directories
			Path path = Paths.get(f.getAbsolutePath());
			try (DirectoryStream<Path> directory = Files.newDirectoryStream(path)) {
				boolean directoryEmpty = directory.iterator().hasNext(); // check if directory is empty or not

				if (!directoryEmpty) { // if dir is empty, backup empty object on S3
					System.out.println(
							"Empty folder detected: " + f.getName() + ". Will create an empty object on S3 now...\n");
					user.putObject(bucket, key + "/" + f.getName() + "/", "");

				}

				boolean b = compare(user, f.getAbsolutePath(), bucket, key + "/" + f.getName());
				if (!b) {
					return false;
				}

			} catch (IOException e) {
				e.printStackTrace();
				return false;
			}

		}
		return true;
	}

}