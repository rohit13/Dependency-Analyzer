##########################
# ReadMe.txt
# Rohit Sharma - SUID -242093353
# Project3_DependencyAnalyzer
##########################

Instructions for running the project.

1. Use compile.bat to comiple the project.
2. Use run.bat to run the project.
There are three arguments provided in the run.bat run command.


Argument 1 : Directory
Argument 2 : Pattern
Argument 3 : Number of threads to start

Argument 2 is comma separated. So, if you want to give multiple extension give them as comma separated string.

e.g. : x64\Debug\ParallelDependencyExecutive.exe ./Inputs *.cpp,*.h 4


For Req 10:
I have tested my code for all the files inside "Inputs" folder in the project.
If you want to test for other folders. Please change the folder name in run.bat script before testing that particular folder.

Note:
Type Table is stored in "Outputs" folder with name "TypeTable_Output_Threaded". Columns are TokenName, Type, Filename, Namespace.
Dependency Table is stored in "Outputs" folder with name "DepTable_Output_Threaded". Files are marked with *. File it depends on marked with -

I have provided a key stroke required method to proceed ahead with analysis on console. This is to enable better analysis in case the output is too long.

If no. of threads > 5 : I Have limited it to 5.