import files;
import string;
import io;
string inputF[] =file_lines(input("input.txt"));
foreach i in inputF{
	printf("output is %d",split(i,",")[2]);
}
