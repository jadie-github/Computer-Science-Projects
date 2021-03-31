/* Jessica Nguyen
 * CSS436, Prog3
 * App.java
 * This program recursively traverses the files of a directory and makes a restore from
the cloud. 
 * */

package com.test.HW3;

import java.io.*;

import com.amazonaws.services.s3.AmazonS3;
import com.amazonaws.services.s3.AmazonS3ClientBuilder;
import com.amazonaws.AmazonClientException;
import com.amazonaws.AmazonServiceException;
import com.amazonaws.services.s3.transfer.MultipleFileDownload;
import com.amazonaws.services.s3.transfer.TransferManagerBuilder;
import com.amazonaws.services.s3.transfer.TransferManager;

public class restore {

	/*
	 * 1: backup/restore 2: backup - local dir ; restore - cloud dir 3: backup -
	 * cloud dir ; restore - local dir
	 */
	public static void main(String[] args) {
		if (args.length != 2) {
			System.err.println("ERROR: Incorrect parameters\n"
					+ "Parameters must be in the form: restore <source>::<destination>");
			return;
		}

		final AmazonS3 user = AmazonS3ClientBuilder.defaultClient();

		restore(user, args[0], args[1]);

	}

	/*
	 * restore()--restore files specified in the S3 bucket “name” of the AWS User
	 * “s3Client” into the local directory “dirPath” Preconditions: dirPath and name
	 * are initialized String objects, s3Client exists in AWS with credentials set
	 * up in your environment Postconditions: returns ERROR if the input name isn’t
	 * in the form bucket::directory. Create a new local directory named “dirPath”
	 * if the input user doesn’t have that local directory. Succesfully restore
	 * cloud files onto local directory
	 * 
	 */
	private static void restore(AmazonS3 s3, String name, String dirPath) {
		if (!name.contains("::")) {
			System.out.println("ERROR: Input bucket must be formatted in the form \"bucketname::directoryName\" only");
			return;
		}

		String[] split = name.split("::");

		if (split.length < 2) {
			System.out.println(
					"ERROR: Empty String detected for bucket and directory strings. Please enter at least 1 character for each");
			return;
		}

		if (name.split("::")[0].isEmpty()) {
			System.out.println("ERROR: Input bucket is an empty String. Please enter at least 1 character");
			return;
		}
		if (name.split("::")[1].isEmpty()) {
			System.out.println("ERROR: Input cloud directory is an empty String. Please enter at least 1 character");
			return;
		}

		String bucket = split[0];
		String cloudDirectory = split[1];

		// assuming that if the local dir doesnt exist we will have to create one and
		// then
		// download the cloud files there
		System.out.println("Path name of input directory is " + dirPath + "\n");

		File folder = new File(dirPath);
		if (!folder.exists()) {
			if (folder.mkdir()) {
				System.out.println("Input directory doesn't exist in client's local directory\nNew directory " + dirPath
						+ " created successfully\n");
			}
		}

		TransferManager mgr = TransferManagerBuilder.standard().build();

		try {
			System.out.println("Restoring to local directory from cloud directory " + name + "...\n");

			MultipleFileDownload files = mgr.downloadDirectory(bucket, cloudDirectory + "/", folder);
			files.isDone();
			files.waitForCompletion();

			System.out.println("Restore to local directory Completed");

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

}