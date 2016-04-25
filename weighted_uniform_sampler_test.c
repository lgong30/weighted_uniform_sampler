#include "weighted_uniform_sampler.h"
#include "random_variable.h"
#include "stdarg.h"

char *pgm_name;
void 
print_linesep()
{
	int i = 0, line_width = 60;
	for (i = 0;i < line_width;++ i)
		printf("=");
	printf("\n");
}

void 
fail(char *message, ...)
{
	va_list args;

	fprintf(stderr, "%s: \n", pgm_name);

	va_start (args,message);
	vfprintf(stderr,message,args);
	va_end(args);

	putchar('\n');

	exit(EXIT_FAILURE);
}

int 
test_correctness(int node_num, int insert[], int delete[],double search[], int in, int dn, int sn, int verbosity)
{
	printf("%s is called ...\n",__func__);
	int i, r, j;
	avl_t *tree = (avl_t *) malloc(sizeof(avl_t));
	tree_create(tree,node_num,NULL);

	if (tree == NULL)
	{
		if (verbosity > 0)
			printf(" 	Out of memory while creating tree.\n");
		return -1;
	}

	if (verbosity > 0)
	{
		printf("	Inserting test ...\n");
	    print_linesep();
	}

    for (i = 0;i < in;++ i)
    {
    	tree_update(tree,insert[i],INCREASE);
    	if (verbosity > 0 && (i + 1) % node_num == 0)
    	{
    		tree_print(tree);
    		printf("\n");
    	}
    }

    if (verbosity > 0)
    {
    	printf("	Searching test ...\n");
    	print_linesep();
    }

    int *ind_array = tree_traverse(tree);
    double total_weight = 0, r_number, TW = TOTAL_WEIGHT(tree);

    for (i = 0;i < sn;++ i)
    {
    	r = tree_probe(tree,search[i]);
    	total_weight = 0;
    	r_number = search[i] * TW;
    	for (j = 0;j < tree->size;++ j)
    	{
    		if (total_weight < r_number)
    			total_weight += SELF_WEIGHT(tree,ind_array[j]);
    		else
    			break;
    	}
    	if (verbosity > 0)
    		printf("Searching %.2f: %4d = %4d\n",search[i], r, ind_array[j - 1]);

    	if (r != ind_array[j - 1]) 
    	{
    		fail("Searching failed");
    	}
    }

    if (verbosity > 0)
    {
    	printf("	deleting test ...\n");
    	print_linesep();
    } 

    for (i = 0;i < dn;++ i)
    {
     	tree_update(tree,delete[i],DECREASE);
    	if (verbosity > 0 && (i + 1) % node_num == 0)
    	{
    		tree_print(tree);
    		printf("\n");
    	}   	
    } 
    tree_destroy(tree);
    printf("%s succeeded ...\n",__func__);

    return 1;
}

int 
main(int argc,char *argv[])
{
	
	int i, in, sn, dn, N;
	N = 256;
	in = 1e3;
	sn = 1e3;
	dn = in / 10;

	pgm_name = argv[0];
	printf("\n\n\n");
	print_linesep();
	printf("	generating random numbers ...\n");
	int *inserts = UniformIntRandomVariable(0,N - 1,in);
	double *rns = UniformDoubleRandomVariable(0,1,sn);
	int *deletes = UniformIntRandomVariable(0,in - 1,dn);

	for (i = 0;i < dn;++ i)
		deletes[i] = inserts[deletes[i]];

	printf("test starts ...\n");
	test_correctness(N,inserts,deletes,rns,in,dn,sn,1);

	free(inserts);
	free(deletes);
	free(rns);

	return 0;
}