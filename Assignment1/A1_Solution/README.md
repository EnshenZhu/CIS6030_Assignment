# <div style="text-align: center;">CIS6030 Information System</div>

## <div style="text-align: center;">Assignment 1</div>

## <div style="text-align: center;"> Enshen Zhu (1194726)</div>

****

## <div style="text-align: center;">Part 1 File Storage and B+ Tree</div>

### A. General Purpose

This script in the Question 1 folder is going to convert the initial data file <b style="color:lightblue">(named as the
A1_data.txt)</b> into the block and record for hard drive disk storage

## <div style="text-align: center;">Part 2 - Linear Hashtable</div>

Due to the system and time constrain, the hash table may not be able to implemented explicitly. The following content
is going to generally describe the fundamental blueprint of the hash-table build-up strategy.

1. Convert the initial data file (with 46882 records) to several data blocks, and each data block should have the
   maximum size of 1024 bytes <b style="color:red">(This step is same to the Question1)</b>
2. When storing each record into the block, the function should return the string-format field 1 value (as the key for
   the following hashing), as well as two short-format value, one is the index of block where this record stays, the
   other is the relative index of this record inside the block.
3. We pre-defined the threshold between the total record (r) and the numbers of bucket (n) to be 5.5. So there would be
   5.5 records in a single bucket on average.
4. After finish the block-record storage. A hash function should take each field 1 value from the newly generated data
   file (which follows the ascending indexing of block and record) as the argument for the hash-value generation. In
   this case, we will employ the ```std::hash```
   from [C++ standard library](https://en.cppreference.com/w/cpp/utility/hash) to convert the field 1 into an 8 byte
   long-format value. For example:
   ```
   long value=std::hash<long>()((long)"aaaaaaaaa");
   cout<<value<<endl;
   
   output: 94601286873468
   ```

5. For each hashed-value from the field 1, we will use a large prime number N to MODE it (only take the residual) into a
   relatively small value. This primitive number N will be regarded as <b style="color:red"> the total number of buckets
   for the linear hashing.</b> (with the bucket index from 0 to N-1).
6. Recall that designed threshold is 5.5, so the final numbers of buckets should not make the r/n exceed 5.5. Therefore,
   the primative number we are going to choose should be over ```46882 / 5.5 = 8524```
7. Take the previous 93922831331708 as an example, we use the primitive number 8527, and get the result of
   ```cout<<94601286873468 % 7901<<endl;``` as 9. So the if the key is "aaaaaaaaa", it will be pointed out into the
   bucket #9, and there would be 8527 buckets in total.
8. The real threshold in this case will be around 5.498 ```(46882 / 8527)```
9. However, the explicit evaluation of hashing performance and hashing collision requires a later programming
   assessment.