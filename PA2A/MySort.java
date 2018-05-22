/**
 * Code for external sort using Merge sort concept.
 */

/**
 * @author Brijesh Mavani
 *
 */
/* Importing required files */
import java.io.File;
import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;




public class MySort {

	/**
	 * @param args
	 */
	// Variable for storing number of threads
	static int numThreads = 0;

	// Time variables
	static long startTime=0, endTime=0, totalTime=0,startMergeTime=0,totalMergeTime=0,startSortTime=0,totalSortTime=0,endMergeTime=0,endSortTime=0;
	
	// Variable for storing block size for each temp file
	static long bSize=0;
	
	// Variable for input and output file name
	static String input="";
	static String output="";
	
	//Variables for calculating memory
	static long freeMem=0;
	static long offset=0;

	// Variables to store input file information
	static int totalFiles=0;
	static long totalLines=0;
	static long fileLength =0;

	
	//Variables for while loop indexing
	static int i=0,j=0,k=0;
	static boolean flag = true;

	// Variables to keep count of lines read during temp file creation 
	static long c=0,l=0;

	// Buffer reader to read file
	static BufferedReader bReader;

	
	// Variable for storing line during file read process.
	static String readLine="";
	
	// Array for storing file data while creating temp files.
	static ArrayList<String> bArray =new ArrayList<String>();	
	
	// Variable for storing temporary file name
	static String tempFile;
		
	// File write for writing temp and output files.
	static FileWriter fout = null;
	
	
	// Variables for storing data temp during sorting process
	static String x="",y="";
	static int index =-1;
	
	// Variables to store read/write information during sorting and merging process
	static long readTempCount=0, writeTempCount=0,readMergeCount=0, writeMergeCount=0,totalReadData=0,totalWriteData=0,totalReadDataGB=0,totalWriteDataGB=0;
	
	// Variables to calculate required output information
	static long IOThroughput=0;
	static long GB = 1000*1000*1000;
	static long MB = 1000*1000;
	static long numBlocks=0;
	
	//Main function
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			if(args.length <2)
			{
				System.out.println("Please pass the input file along with number of threads.");
				System.out.println("Usage: java MySort <FileName> <NumberOfThreads>");
				System.exit(0);
			}

			String inputFileName= args[0];
			System.out.println("1st Argument: "+inputFileName );
			numThreads = Integer.parseInt(args[1]);
			System.out.println("2nd Argument: "+numThreads);
			input= "/input/";
			
			input=input.concat(inputFileName);
			System.out.println("Input file: "+input);
			
			output ="/tmp/outputBrijesh.dat";
			
			numBlocks=(inputFileName.compareTo("data-2GB.in")==0)?100:32;
			System.out.println("NumBlocks value: "+numBlocks);
			File inputFile = new File(input);
			File outputFile = new File(output);

			// check whether file exists
			if(!inputFile.exists())
			{
				System.out.println("Unable to locate file: "+input+". Please check and re-execute with correct file name.");
				System.exit(-1);
			}
			//Garbage collection before finding available free memory
			System.gc();
			freeMem = Runtime.getRuntime().freeMemory();
			System.out.println("Currently available free memory is: "+freeMem);

			fileLength=inputFile.length();
			System.out.println("Input file Length is: "+fileLength);
			
			/*if(fileLength%256!=0)
			{
				offset=1;
			}

			// Calculate the block size for temp file.
			bSize = (fileLength/1024)+offset;*/
			//bSize= ((bSize<freeMem/2)&&(fileLength>freeMem))?(freeMem/2):bSize;  // In case available memory is more than calculated block size.
			bSize= ((bSize<freeMem/2)&&(fileLength>freeMem))?(freeMem/numBlocks):bSize;  
			/*if(fileLength>=freeMem)
			{
				bSize=freeMem/150;
			}
			else
			{
				bSize=fileLength/100;
			}*/
			System.out.println("Block Size for each temp file is: "+bSize);

			bReader = new BufferedReader(new FileReader(inputFile));
			System.out.println("Buffer Reader Created!!");


			System.out.println("Starting clock for execution!!");

			// Start clock for calculating total execution time
			startTime =System.currentTimeMillis();
			//System.out.println("Start Time: "+startTime);

			while(flag)
			{
				readLine = null;
				c= l +0 ; // initial values for counters;
				
				//System.out.println("Before While values C: "+c+" L: "+l);
				//System.out.println("c + bSize: "+(c+bSize));
				
				while(l< (c+bSize))
				{
					readLine = bReader.readLine();					
					if(readLine == null)
					{
						System.out.println("Empty line. Exit loop");
						break;
					}
					else
					{
						bArray.add(readLine);						
						readTempCount++;
						/*if (l%1000000 ==0)
						{
							System.out.println("L: "+l);
						}*/
					}
					l++;
				}
				//System.out.println("after While values C: "+c+" L: "+l);
				if(readLine== null)
				{
					if(bArray.isEmpty())
					{
						System.out.println("Empty line + block array is empty. Exit loop.");
						break;
					}
					else
					{
						l = l + bSize;
					}
				}
				

				//System.out.println("Block array size before sorting: "+bArray.size());
				// Start clock for calculating sort time
				startSortTime = System.currentTimeMillis();
				//System.out.println("Calling Merge Sort!!");
				bArray = mergeSort(bArray, 0, bArray.size()-1, numThreads);
				
				//System.out.println("Block array size after sorting: "+bArray.size());
				//Write sorted array into temp file
				tempFile = "/tmp/Tempfile"+(l/bSize)+".dat";
				//System.out.println("Temp File name: " +tempFile);

				fout =new FileWriter(new File(tempFile));
				j=0;
				while(j<bArray.size())
				{
					fout.write(bArray.get(j)+"\r\n");
					j++;
					writeTempCount++;
				}
				//writeTempCount+=tempFile.length();
				//System.out.println("Value of J at end of loop: "+j);
				//close the file writer after writing a file.
				fout.close();
				endSortTime = System.currentTimeMillis();

				totalSortTime += (endSortTime - startSortTime);

				
				//clear the array for next block
				bArray.clear();
			}
			//close the buffer reader after reading entire file and creating temp files.
			bReader.close();			
			
			System.out.println("Total time taken for creating temp files and sorting: "+(totalSortTime/1000) +" sec");

			System.out.println("Read count for creating Temp files: "+readTempCount);
			System.out.println("write count for creating Temp files: "+writeTempCount);
			fout = new FileWriter(outputFile);  // For writing files.
			totalFiles = (int) (l/bSize);
			
			System.out.println("Total "+totalFiles + " temporary files are created.");
			
			//create array to save total no of lines in each file.
			//long n[] = new long [totalFiles];

			//create array to save single line from each file.
			String m[] = new String [totalFiles];			

			// Create new buffer reader array to read totalFiles.
			BufferedReader bArrayNew[] = new BufferedReader [totalFiles];
			k=0;
			while (k<totalFiles)
			{
				tempFile = "/tmp/Tempfile"+(k+1)+".dat";
				//System.out.println("tempFile : "+tempFile);
				bArrayNew[k]=new BufferedReader(new FileReader(new File(tempFile)));
				//n[k]=fileLength/100;
				k++;
			}
			startMergeTime = System.currentTimeMillis();
			i=0;
			//System.out.println("FileLengh / 100 : "+(fileLength/100));
			while (i<(fileLength/100))  // Each record is of 100 bytes.
			{
				j=0;
				/*if(i%1000000==0)
				{
					System.out.println("in I loop "+i);
				}*/

				while(j<totalFiles)
				{
					x = m[j];
					if(x!=null)
					{
						if(x.equals(""))
						{
							j++;
							continue;
						} 
						y=y.equals("")?x:y;
						/* combined both statements into single if to reduce 1 if condiction evaluation and assignment
						y=(x.compareTo(y)<=0)?x:y;
						index=(x.compareTo(y)<=0)?j:index;
						*/
						if(x.compareTo(y)>0){
						  // do nothing 
						}
						else{
						y=x;
						index=j;	
						}						
					}
					else
					{
						x=bArrayNew[j].readLine();
						readMergeCount++;
						if(x==null)
						{
							m[j]="";
						}
						else
						{
							y=y.equals("")?x:y;
						/* combined both statements into single if to reduce 1 if condiction evaluation and assignment
						y=(x.compareTo(y)<=0)?x:y;
						index=(x.compareTo(y)<=0)?j:index;
						*/
						if(x.compareTo(y)>0){
						  // do nothing 
						}
						else{
						y=x;
						index=j;	
						}	
						m[j]=x;
						}
					}
					j++;	
					
				}

				fout.write(y+"\r\n");
				y=""; // resetting y to null;
				m[index]=null;
				writeMergeCount++;
				i++;
			}
			
			endMergeTime=System.currentTimeMillis();
			totalMergeTime = endMergeTime-startMergeTime;
			fout.close();
			i=0;
			//close the array and delete the temp files.
			/*while(i<totalFiles)
			{
				bArrayNew[i].close();
				//new File("/tmp/Tempfile"+(i+1)+".dat").delete();
				i++;
			}*/
			
			
			System.out.println("Total Merge Time : "+(totalMergeTime/1000) +" sec");
			System.out.println("Total Execution Time: "+((endMergeTime-startTime)/1000) +" sec");
			
			
			System.out.println("Read count for Merge operation : "+readMergeCount);
			System.out.println("write count for Merge operation: "+writeMergeCount);
			
			totalReadData=(readMergeCount+readTempCount)*100L;
			totalWriteData=(writeMergeCount+writeTempCount)*100L;
			
			//System.out.println("GB is: "+GB);
			
			totalReadDataGB=(long)(totalReadData/GB);
			totalWriteDataGB=(long)(totalWriteData/GB);
	/*		System.out.print("Read: ");
			System.out.println(totalReadDataGB);
			System.out.print("\nWrite: ");
			
			System.out.println(totalWriteDataGB);*/
			IOThroughput= (((totalReadData+totalWriteData)/MB)/((endMergeTime-startTime)/1000));
			
			System.out.println("Total count for Read Data : "+totalReadData+ " Bytes i.e. "+totalReadDataGB+ " GB.");
			System.out.println("Total count for Write Data: "+totalWriteData+ " Bytes i.e. "+totalWriteDataGB+ " GB.");
			
			System.out.println("Output file length: "+ outputFile.length());
			
			System.out.println("IO Throughput is: "+IOThroughput+" MB/Sec");
			System.out.println("Execution completed!!");
		}
		catch (NumberFormatException nfe) {
			System.out.println("The second argument is for number of threads and must be an integer.");
			System.exit(-1);
		}
		catch(Exception e)
		{
			System.out.println("Exception occurred!!");
			e.printStackTrace();
			System.exit(-1);
		}
	}


	private static ArrayList<String> mergeSort(ArrayList<String> bArray2, long start, long end, int numThreads2) {
		// TODO Auto-generated method stub
		//System.out.println("In merge sort");
		long mid =0;
		ArrayList<String> L = null, R = null;
		MergeThread left = null;
		ArrayList<String> t = new ArrayList<String>();

		mid = (start+end)/2;
		Thread leftThread = null;

		if(start>end)
		{
			//System.out.println("start > end");
			return t;
			//return new ArrayList<String>();
		}
		else if(start==end)
		{
			//ArrayList<String> t = new ArrayList<String>();
		//	System.out.println("start == end");
			t.add(bArray2.get((int)start));
			return t;			
		}

		//Sort left half
		if(numThreads2<=1)
		{
			L = mergeSort(bArray2, start, mid, numThreads2/2);
		}
		else
		{
			left = new MergeThread(bArray2, start, mid, numThreads2/2);
			leftThread = new Thread(left);
			//System.out.println("Starting Thread!!");
			leftThread.start();
		}
		R = mergeSort(bArray2, mid+1, end, numThreads2 - (numThreads2/2));
		if(numThreads2 > 1){
			try {
				//System.out.println("Joining Thread!!");
				leftThread.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				System.err.println("Exception occured during left thread join process.");
			}
			L = left.getData();
		}

		return merge(L, R);	
	}


	private static ArrayList<String> merge(ArrayList<String> l2, ArrayList<String> r2) {
		// TODO Auto-generated method stub
		int lIndex=0;
		int rIndex=0;
		long p=0;
		ArrayList<String> tempBlock =new ArrayList<String>();
		int compare = 0;
		//System.out.println("L2 size: "+l2.size() + " R2 size: "+r2.size());
		while(p<(l2.size()+r2.size()))
		{
			if(rIndex>= r2.size())
			{
				//System.out.println("right block");
				tempBlock.add(l2.get(lIndex));
				lIndex = lIndex + 1;
			}
			else if(lIndex>= l2.size())
			{
				//System.out.println("left block");
				tempBlock.add(r2.get(rIndex));
				rIndex = rIndex + 1;	
			}
			else
			{
				compare = l2.get(lIndex).compareTo(r2.get(rIndex));
				//System.out.println("Compare : "+compare);

				if(compare> 0)
				{
				//System.out.println("compare > 0 ");
				tempBlock.add(r2.get(rIndex));
				rIndex = rIndex + 1;
			}
			else if(compare<= 0)
			{
				//System.out.println("compare < =0");
				tempBlock.add(l2.get(lIndex));
				lIndex = lIndex + 1;
			}
			}
			p= p+1;
			//System.out.println("P: "+p);
		}		
		return tempBlock;		
	}


	private static class MergeThread implements Runnable{
		private ArrayList<String> block;
		private ArrayList<String> blockResult;
		private long start,end;
		private int nThreads;

		public MergeThread(ArrayList<String> block, long start, long end, int nThreads) {
			// TODO Auto-generated constructor stub
			this.block= block;
			this.start= start;
			this.end= end;
			this.nThreads = nThreads;
		}

		public ArrayList<String> getData(){
			return blockResult;
		}

		@Override
		public void run() {
			// TODO Auto-generated method stub
			blockResult = mergeSort(block, start, end, nThreads);
		}
	}	


}