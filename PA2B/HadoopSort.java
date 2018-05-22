/**
 * Code for Hadoop Sort
 */

/**
 * @author Brijesh Mavani
 *
 */
/* Importing required files */
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.Mapper;
import java.io.IOException;


public class HadoopSort extends Configured implements Tool
{
	/**	
	* @param args
	*/
	
	public static class HadoopSortMapper extends Mapper<LongWritable, Text, Text, Text>

{
	//define objects for key and value of map output
	private Text mKey = new Text();  // object to hold key of output
	private Text mValue = new Text(); // object to hold value of output
	@Override
	public void map(LongWritable key, Text value, Context context)
		throws IOException, InterruptedException
	{
				
		String[] slice = null;
		String line = value.toString();
		//  end of line will be marked as "\n".
		slice = line.split("\\n"); 
		
		for ( int i=0; i < slice.length; i++)
		{
			// file contains 10 bytes of key at beginning
			mKey.set(slice[i].substring(0, 10)); 
			
			// Remaining 90 bytes are values/Data
			mValue.set(slice[i].substring(10)); 
			
			// write key and value into mapper context	
			context.write(mKey, mValue); 
		}
	}
}

public static class HadoopSortReducer extends Reducer<Text, Text, Text, Text>
{	
	//It functionality of reducer is to go through shuffle and then sort. After sorting final sorted output will be written into context. 
	
	@Override
	public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException
	{
		
		Text output = null ;
		for(Text value : values)
		{
			// Assign input to output of reducer
			output = value; 
		}
		//write output of reducer to the context
		context.write(key, output); 
	}
		
}

	@Override
	public int run(String[] args) throws Exception
	{
		// Time variables
		long startTime=0, endTime=0;
		
		//execution flag
		int flag=0;
	
		//validate arguments for input and output files with path
		if(args.length <2)
		{
			System.out.println("Please pass the input file and output file names with path.");
			//System.out.println("Usage: java MySort <FileName> <NumberOfThreads>");
			System.exit(0);
		}
		
		// Start the timer for the execution 
		startTime = System.currentTimeMillis();		
		
		//create new job
		@SuppressWarnings("deprecation")
		Job job = new Job();
		job.setJarByClass(HadoopSort.class);
		job.setJobName("Hadoop Sort");
		
		// assign input file
		FileInputFormat.addInputPath(job, new Path(args[0]));

		// assign output file
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		//assign mapper class for Map function
		job.setMapperClass(HadoopSortMapper.class);
		
		//assign combiner class. For this case, I am using Reducer Class only.
		job.setCombinerClass(HadoopSortReducer.class);
		
		//assign reducer class for Reduce function
		job.setReducerClass(HadoopSortReducer.class);
		
		//set output datatype for key of Reduce function
		job.setOutputKeyClass(Text.class);
		
		//set output datatype for value of Reduce function
		job.setOutputValueClass(Text.class);
		
		//wait till job completes
 		flag = job.waitForCompletion(true) ? 0 : 1;
		
		// end the timer for the execution 
		endTime = System.currentTimeMillis();
		if (flag ==1)
		{
			System.out.println("Total Elapsed Time "+ (endTime-startTime) + "ms for Hadoop execution.");
		}
		else
		{
			System.out.println("Total Elapsed Time "+ (endTime-startTime) + "ms for Hadoop execution.");
		}
		
		return flag;
	}
	
	//Main function
	public static void main(String[] args) throws Exception
	{
		// TODO Auto-generated method stub				
		
		// using ToolRunner to run the code
		//int exitCode = ToolRunner.run(new Configuration(), new TeraSortHadoopDriver(), args);
		int exitCode = ToolRunner.run(new HadoopSort(), args);
		System.exit(exitCode);		
			
	}
}
