#include "bptree.h"
#include <vector>
#include <sys/time.h>
#include <random>

using namespace std;

void non_leaf_split(NODE *leaf, int key, DATA *data);

struct timeval
cur_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}

void
print_tree_core(NODE *n)
{
	printf("["); 
	for (int i = 0; i < n->nkey; i++) {
		if (!n->isLeaf) print_tree_core(n->chi[i]); 
		printf("%d", n->key[i]); 
		if (i != n->nkey-1 && n->isLeaf) putchar(' ');
	}
	if (!n->isLeaf) print_tree_core(n->chi[n->nkey]);
	printf("]");
}

void
print_tree(NODE *node)
{
	print_tree_core(node);
	printf("\n"); fflush(stdout);
}

NODE *
find_leaf(NODE *node, int key)
{
	int kid;

	if (node->isLeaf) return node;
	for (kid = 0; kid < node->nkey; kid++) {
		if (key < node->key[kid]) break;
	}

	return find_leaf(node->chi[kid], key);
}

NODE *
insert_in_leaf(NODE *leaf, int key, DATA *data)
{
	int i;

	if (key < leaf->key[0]) {
		// insert head
		// 0 -> [1,2]
		//   -> [0, 1, 2]
		for (i = leaf->nkey; i > 0; i--) {
			leaf->chi[i] = leaf->chi[i-1] ;
			leaf->key[i] = leaf->key[i-1] ;
		} 
		leaf->key[0] = key;
		leaf->chi[0] = (NODE *)data;
	}
	else
	{
		// search
		// 3 -> [2,*4,6]
		for (i = 0; i < leaf->nkey; i++) {
			if (key < leaf->key[i]) break;
		}
		// move
		// -> [2,4,4,6]
		for (int j = leaf->nkey; j > i; j--) {		
			leaf->chi[j] = leaf->chi[j-1] ;
			leaf->key[j] = leaf->key[j-1] ;
		}

		// insert
		// -> [2,3,4,6]
		leaf->key[i] = key;
		leaf->chi[i] = (NODE *)data;
	}
	leaf->nkey++;

	return leaf;
}

NODE *
alloc_leaf(NODE *parent)
{
	NODE *node;
	if (!(node = (NODE *)calloc(1, sizeof(NODE)))) ERR;
	node->isLeaf = true;
	node->parent = parent;
	node->nkey = 0;

	return node;
}

TEMP *
alloc_temp(void)
{
	TEMP *temp;
	
	if (!(temp = (TEMP *)calloc(1, sizeof(TEMP)))) ERR;
	temp->isLeaf = true;
	temp->nkey = 0;
	return temp;
}

void
insert_in_parent(NODE *leaf, int key, NODE *data)
{
	int i;

	if (leaf->nkey < (N-1))
	{
		for (i = 0; i < leaf->nkey && leaf->key[i] <= key; i++);

		for (int j = leaf->nkey; j > i; j--)
		{
			//printf("j%d : %d\n", j, leaf->key[j-1]);
			leaf->chi[j + 1] = leaf->chi[j];
			leaf->key[j] = leaf->key[j-1];
		}

		leaf->chi[i+1] = data;
		leaf->key[i] = key;

		leaf->nkey++;
		return ;
	}
	else
	{
		non_leaf_split(leaf, key, (DATA *)data);
	}
}

void insert_in_not_leaf(NODE *node, int key, DATA *data)
{
	int i;
	// search
	// 3 -> [2,*4,6]
	for (i = 0; i < node->nkey; i++) {
		if (key < node->key[i]) break;
	}
	// move
	// -> [2,4,4,6]
	for (int j = node->nkey + 1; j > i; j--) {		
		node->chi[j] = node->chi[j-1];
		if (j != node->nkey + 1)
		{
			node->key[j] = node->key[j-1];
		}
	}

	// insert
	// -> [2,3,4,6]
	node->key[i] = key;
	node->chi[i+1] = (NODE *)data;
	node->nkey++;
}

// leaf_splitとnon_leaf_splitが合体してしまったもの
void non_leaf_split(NODE *leaf, int key, DATA *data)
{
	TEMP *T;
	NODE *Pd;
	int	 mid;

	if (leaf->parent == NULL)
	{
		//printf("new root\n");
		leaf->parent = (NODE *)calloc(1,sizeof(NODE));
		leaf->parent->chi[0] = leaf;
		leaf->parent->isLeaf = false;
		Root = leaf->parent;
	}

	T = alloc_temp();
	for (int i = 0; i < leaf->nkey + !leaf->isLeaf; i++)
	{
		T->chi[i] = leaf->chi[i];
		T->key[i] = leaf->key[i];
		//printf("copy %d:%d\n", i, leaf->key[i]);
	}
	T->nkey = leaf->nkey;

	//printf("nkey : %d\n", leaf->nkey);
	if (leaf->isLeaf)
	{
		insert_in_leaf((NODE *)T, key, data);
	}
	else
	{
		insert_in_not_leaf((NODE *)T, key, data);	
	}
	//print_tree((NODE *)T);
	//printf("inserted %d\n", key);

	Pd = alloc_leaf(leaf->parent);
	Pd->isLeaf = leaf->isLeaf;
	mid = T->nkey / 2;

	//printf("mid %d\n", mid);
	for (int i=0; i < mid + !leaf->isLeaf; i++)
	{
		if (i != mid || leaf->isLeaf)
			leaf->key[i] = T->key[i];
		leaf->chi[i] = T->chi[i];
	}
	leaf->nkey = mid;

	// printf("%d\n", leaf->isLeaf);
	for (int i=mid; i < T->nkey; i++)
	{
		if (leaf->isLeaf)
		{
			Pd->key[i-mid] = T->key[i];
			Pd->chi[i-mid] = T->chi[i];
		}
		else
		{
			if (i - mid != 0)
			{
				Pd->key[i-mid-1] = T->key[i];
			}
			//printf("h %d %d\n", i, T->nkey);
			Pd->chi[i-mid] = T->chi[i + 1];
			Pd->chi[i-mid]->parent = Pd;
		}
	}
	Pd->nkey = T->nkey - mid - !leaf->isLeaf;

	//printf("l %p\n", leaf);
	//print_tree(leaf);
	//printf("n %p\n", Pd);
	//print_tree(Pd);

	insert_in_parent(leaf->parent, T->key[mid], Pd);
}

void 
insert(int key, DATA *data)
{
	NODE *leaf;

	if (Root == NULL) {
		leaf = alloc_leaf(NULL);
		Root = leaf;
	}
	else {
		leaf = find_leaf(Root, key);
	}

	if (leaf->nkey < (N-1)) {
		insert_in_leaf(leaf, key, data);
	}
	else {
		non_leaf_split(leaf, key, data);
	}
}

void
init_root(void)
{
	Root = NULL;
}

int 
interactive()
{
  int key;

  std::cout << "Key: ";
  std::cin >> key;

  return key;
}

std::vector<int> OriginalInput; 

void init(int size)
{
  for(int i = 0; i < size; i++) {
    OriginalInput.push_back(i);
  }
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(OriginalInput.begin(), OriginalInput.end(), engine);
}

void put_time(timeval begin, timeval end)
{
	uint64_t b = (begin.tv_sec * (uint64_t)1000) + (begin.tv_usec / 1000);
	uint64_t e = (end.tv_sec * (uint64_t)1000) + (end.tv_usec / 1000);
	printf("%llums", e - b);
}

int
main(int argc, char *argv[])
{
	struct timeval begin;

	if (argc == 1)
	{
		printf("Usage %s size\n", argv[0]);
		return 0;
	}
	int size = atoi(argv[1]);
	init(size);

	init_root();

	begin = cur_time();
	/*
	printf("-----Insert-----\n");
	while (true) {
		insert(interactive(), NULL);
    	print_tree(Root);
	}
	*/
	
	//int auau[] = {1,4,5,3,8,9,7,6,2,0};

	printf("Size : %d\n", size);

	for (int i = 0; i < size; i++)
	{
		//insert(auau[i], NULL);
		insert(OriginalInput[i], NULL);
    	//print_tree(Root);
	}
	//print_tree(Root);

	printf("Insert Time : ");
	put_time(begin, cur_time());
	printf("\n");

	/*
	for (int i = 0; i < size; i++)
	{
		printf("%d ", OriginalInput[i]);
	}
	printf("\n");
    print_tree(Root);
	*/

	begin = cur_time();
	for (int i = 0; i < size; i++)
	{
		NODE *l = find_leaf(Root, i);
		bool find = false;
		for (int j = 0; j < l->nkey; j++)
		{
			if (l->key[j] != i) continue;
			find = true;
			break;
		}
		if (!find)
		{
			printf("not found %d\n", i);
		}
	}
	
	printf("Search Time : ");
	put_time(begin, cur_time());
	printf("\n");

	return 0;
}
