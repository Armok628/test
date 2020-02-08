#ifndef VOCAB_H
#define VOCAB_H
/*
 *	Tools for generating the Forth vocabulary
 */

struct fthdef {
	struct fthdef *prev;
	char *name;
	bool imm : 1;
	cell len : 8*sizeof(cell)-1;
	void *cf;
	void **data[];
};

// Used in the VOCAB X macro below to generate fthdef structs.
// The line filling in .cf is commented out because its value should be local to engine.
// It should be filled in when engine is called with a NULL instruction pointer.
#define DEF(cn,pr,nm,im,cf,...) \
struct fthdef cn = { \
	.prev = pr, \
	.name = nm, \
	.imm = im, \
	.len = COUNT(nm), \
	/*.cf = cf,*/ \
	.data = {__VA_ARGS__}, \
};

// Used in the VOCAB X macro below to generate a list of code fields.
#define CF(cn,pr,nm,im,cf,...) cf,

// Used in the varargs of a VOCAB entry to compile code by hand.
#define XT(cn) &cn##_d.cf
#define LIT(n) XT(lit),(void **)(n)

// VOCAB is an X-macro containing a list of Forth definitions.
// Definition ID's are postfixed with "_d" to avoid collision.
// Likewise, labels in the engine are postfixed with "_c".
#define VOCAB(X) \
	X(bye_d,NULL,"BYE",0,&&bye_c) \
	X(lit_d,&bye_d,"LIT",0,&&lit_c) \
	X(exit_d,&lit_d,"EXIT",0,&&exit_c) \
	X(docol_d,&exit_d,"DOCOL",0,&&docol_c) \
	X(dup_d,&docol_d,"DUP",0,&&dup_c) \
	X(drop_d,&dup_d,"DROP",0,&&drop_c) \
	X(swap_d,&drop_d,"SWAP",0,&&swap_c) \
	X(rot_d,&swap_d,"ROT",0,&&rot_c) \
	X(add_d,&rot_d,"+",0,&&add_c) \
	X(cell_d,&add_d,"CELL",0,&&docol_c, \
		LIT(sizeof(cell)),XT(exit) \
	) \
// LAST_VOC is needed for the engine to know where to start filling in code fields
#define LAST_VOC &cell_d

#endif