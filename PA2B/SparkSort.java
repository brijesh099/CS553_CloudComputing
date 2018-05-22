/**
 * Code for Spark Sort
 */

/**
 * @author Brijesh Mavani
 *
 */

import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.api.java.function.FlatMapFunction;
import org.apache.spark.api.java.function.PairFunction;

import scala.Tuple2;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

public final class SparkSort
{
  	/**	
	* @param args
	*/
	
  public static void main(String[] args) throws Exception 
  {
	  // Time variables
	long startTime=0, endTime=0;
		
	// TODO Auto-generated method stub	
    	if(args.length <2)
		{
			System.out.println("Please pass the input file and output file names with path.");
			//System.out.println("Usage: java MySort <FileName> <NumberOfThreads>");
			System.exit(0);
		}

		
	//set App Name	
	SparkConf sparkConf = new SparkConf().setAppName("SparkSort");
	
	// set spark context
    JavaSparkContext jsc = new JavaSparkContext(sparkConf);

	// Start the timer for the execution 	
	startTime = System.currentTimeMillis();
	
	// assign input file
	JavaRDD<String> textFile = jsc.textFile(args[0]);
	
	
	JavaPairRDD<String, String> SortedOp = textFile.mapToPair(word -> new Tuple2<>(word.substring(0,10), word.substring(10))).sortByKey(true);
	
	// save output at output path given in arguments	
	SortedOp.saveAsTextFile(args[1]);
	
	// end the timer for the execution 
	endTime = System.currentTimeMillis();
	
	System.out.println("Total Elapsed Time "+ (endTime-startTime) + "ms for Spark execution.");
    //spark.stop();
  }
  
}