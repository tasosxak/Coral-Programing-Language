#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "coraldefs.h"
#include "y.tab.h"



extern AstNode *TreeRoot;


int TAG_IFS = -1; //Number of if-else statements 
int TAG_WHILES =-1; //Number of while-loop statements
int REG_A_IN_USE = 0; //True if register-AX is in use or not
int BYTES_OF_PARAMETERS = 0;
int NUM_OF_LITERALS = 0;
int LOC_ASSIGN_COUNTER =0;
int R_TYPES_COUNTER = 0;

int NUM_OF_INT_CONST = 0;
int NUM_OF_REAL_CONST = 0;

symbol* assigns[50];
int r_types[50];

FILE *text, *data;

void kena(int n)
{  int i;
   
   for(i=0; i<n; i++) printf(" ");
}

void traverse(AstNode *p,int n)
{  int i;

   n=n+3;
   if(p)
   {
      switch (p->NodeType)
      {
         case astEmptyProgram: 
            kena(n); printf("astEmptyProgram\n"); 
         break;
         case astProgram: 
            kena(n); printf("astProgram\n"); 
         break;
         case astMethSeq: 
            kena(n); printf("astMethSeq\n"); 
         break;
         case astMethLast: 
            kena(n); printf("astMethLast: %s\n",p->SymbolNode->name); 
         break;
         case astParamSeq: 
            kena(n); printf("astParamSeq\n"); 
         break;
         case astParamEmpty: 
            kena(n); printf("astParamEmpty\n"); 
         break;
         case astFormalsSeq: 
            kena(n); printf("astFormalsSeq\n"); 
         break;
         case astFormalsEmpty: 
            kena(n); printf("astFormalsEmpty\n"); 
         break;
         case astInt: 
            kena(n); printf("astInt\n"); 
         break;   
         case astIfElseStmt: 
            kena(n); printf("astIfElseStmt\n"); 
         break;
         case astBody: 
            kena(n); printf("astBody\n"); 
         break;
         case astDeclsSeq: 
            kena(n); printf("astDeclsSeq\n"); 
         break;
         case astDeclsEmpty: 
            kena(n); printf("astDeclsEmpty\n"); 
         break;
         case astDeclListSeq:
            kena(n); printf("astDeclListSeq\n"); 
         break;
         case astDeclListEmpty: 
            kena(n); printf("astDeclListEmpty\n"); 
         break;
         case astDecl: 
            kena(n); printf("astDecl\n"); 
         break;
         case astDeclAssign: 
            kena(n); printf("astDeclAssign\n"); 
         break;
         case astVarsSeq: 
            kena(n); printf("astVarsSeq\n"); 
         break;
         case astVarAssign:
            kena(n); printf("astVarAssign\n"); 
         break;
         case astVarEmpty: 
            kena(n); printf("astVarEmpty\n"); 
         break;
         case astStmtSeq: 
            kena(n); printf("astStmtSeq\n"); 
         break;
         case astStmtEmpty: 
            kena(n); printf("astStmtEmpty\n"); 
         break;
         case astLocation: 
            kena(n); printf("astLocation: %s\n",p->SymbolNode->name); 
         break;
         case astReturnStmt:
            kena(n); printf("astReturnStmt\n"); 
         break;
         case astMethodName: 
            kena(n); printf("astMethodName: %s\n",p->SymbolNode->name); 
         break;
         case astWhileStmt: 
            kena(n); printf("astWhileStmt\n"); 
         break;
         case astBreakStmt: 
            kena(n); printf("astBreakStmt\n"); 
         break;
         case astCompExpr: 
            kena(n); printf("astCompExpr\n"); 
         break;
         case astAssign: 
            kena(n); printf("astAssign\n"); 
         break;
         case astAddExpr: 
            kena(n); printf("astAddExpr\n"); 
         break;
         case astAddExprLast: 
            kena(n); printf("astAddExprLast\n"); 
         break;
         case astNullStmt: 
            kena(n); printf("astNullStmt\n"); 
         break;
         case astMethodCall: 
            kena(n); printf("astMethodCall: %s\n",p->SymbolNode->name); 
         break;
         case astGeOp: 
            kena(n); printf("astGeOp\n"); 
         break;
         case astGOp: 
            kena(n); printf("astGOp\n"); 
         break;
         case astLeOp: 
            kena(n); printf("astLeOp\n"); 
         break;
		 case astLOp: 
            kena(n); printf("astLOp\n"); 
         break;
		 case astNeOp: 
            kena(n); printf("astNeOp\n"); 
         break;
		 case astEOp: 
            kena(n); printf("astEOp\n"); 
         break;
		 case astAddOp: 
            kena(n); printf("astAddOp\n"); 
         break;
		 case astSubOp: 
            kena(n); printf("astSubOp\n"); 
         break;
		 case astMulExpr: 
            kena(n); printf("astMulExpr\n"); 
         break;
		 case astMulOp: 
            kena(n); printf("astMulOp\n"); 
         break;
		 case astDivOp: 
            kena(n); printf("astDivOp\n"); 
         break;
		 case astDeConst: 
            kena(n); printf("astDeConst\n"); 
         break;
		 case astTrue: 
            kena(n); printf("astTrue\n"); 
         break;
		 case astActualsEmpty: 
            kena(n); printf("astActualsEmpty\n"); 
         break;
		 case astFalse: 
            kena(n); printf("astFalse\n"); 
         break;
		 case astActuals: 
            kena(n); printf("astActuals\n"); 
         break;
		 case astArgsSeq: 
            kena(n); printf("astArgsSeq\n"); 
         break;
		 case astArgsEmpty: 
            kena(n); printf("astArgsEmpty\n"); 
         break;
         default: 
            printf("Unknown=%d\n",p->NodeType);
      }
      for(i=0; i<4; i++) traverse(p->pAstNode[i],n);
   }
}

//-------------Processes for Code Generation ---------------//


//Program
void ProcessProgram(AstNode*p, int lev){	
   CodeGeneration(p->pAstNode[0],lev+1,0,0);
   
}

//Methods
void ProcessMethSeq(AstNode*p, int lev){	
   CodeGeneration(p->pAstNode[0],lev+1,0,0);
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

//Method
void ProcessMethLast(AstNode*p, int lev){	
  
	BYTES_OF_PARAMETERS = 0;
	//Code Generation for parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	   
	//Method definition
	fprintf(text,"_%s:\n",p->SymbolNode->name);
	fprintf(text,"push ebp\n");
	fprintf(text,"mov ebp,esp\n");
	if(strcmp(p->SymbolNode->name,"main") == 0)
		fprintf(text,"fldcw [cw]\n");
		
		
	//BYTES_OF_PARAMETERS = 4 * p->SymbolNode->dcl_ptr->num_params;
	
	//Code Generation for statements
	CodeGeneration(p->pAstNode[2],lev+1,0,1);
	   
	fprintf(text,"\n\n");
}

//Body
void ProcessBody(AstNode*p, int lev){	
   CodeGeneration(p->pAstNode[0],lev+1,0,1);
   CodeGeneration(p->pAstNode[1],lev+1,0,1);
}

//Statements
void ProcessStmtSeq(AstNode*p, int lev){	
   CodeGeneration(p->pAstNode[0],lev+1,0,1);
   CodeGeneration(p->pAstNode[1],lev+1,0,1);
}
/*
//Library List
void ProcessLibList(AstNode *p, int lev, int leftChild){
	
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
	
	
}*/
/*
//Library
void ProcessLib(AstNode *p, int lev, int leftChild){
	
	system("copy data.asm + text.asm program.asm");
	system("del data.asm");
	system("del text.asm");
	fprintf(text,"%%include \"%s\"\n",p->SymbolNode->name);
}
*/


// Expr Statement
void ProcessExprStmt(AstNode *p, int lev, int lvalue,int leftChild){
	
	symbol *lhs;
	
	CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	pop_vs();
	
	
}

// While Statement
void ProcessWhileStmt(AstNode *p, int lev, int lvalue,int leftChild)
{ 
   symbol *rhs, *wh;
   int TEMP_TAG_WHILE;
   TAG_WHILES++;
   TEMP_TAG_WHILE= TAG_WHILES;
   
   //While definition
   fprintf(text,"@WHILE_%d:\n",TEMP_TAG_WHILE);
   
   //Code Generation for the logical expression 
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
   rhs=pop_vs();
   
   if(rhs->typos != BOOL){
	   
	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",rhs->typos);
	   exit(1);
	   
   }
   
    
   if( rhs->sclass == REGISTER )
   {
	   /*Push a symbol to whiles stack, this helps 
	    'break' statements to recognize in which while-statement 
		they belong to */
		
	   wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);
	   
	   fprintf(text,"mov ecx,[rgs]\n");
       fprintf(text,"jcxz @ENDWHILE_%d\n",TEMP_TAG_WHILE);
	   
	   //Code Generation statements in while-loop
       CodeGeneration(p->pAstNode[1],lev+1,0,0); 
	   fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
	   fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
	   
	   pop_wh();
	   
   }
   else if( rhs->sclass == MEMORY ) 
   {  
       wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);
	   
       fprintf(text,"mov ecx,[%s]\n",rhs->pseudonym);
       fprintf(text,"jcxz @ENDWHILE_%d\n",TEMP_TAG_WHILE);
	   
       CodeGeneration(p->pAstNode[1],lev+1,0,0); 
	   fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
	   fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
	   
	   pop_wh();
	   
   }
   else /* --- CONSTANT --- */
   {  
      if( rhs->timi != 0 )
      {
		 wh = new_symbol("");
	     wh->timi = TEMP_TAG_WHILE;
	     push_wh(wh);
	   
         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
		 
		 fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
		 
		 pop_wh();
      }
     
   }
   
   
   
}

//Dec Constant (Integer)
void ProcessDeConst(AstNode *p) 
{ 
   push_vs(p->SymbolNode);
}

//Real Dec Constant (Real)
void ProcessRealDeConst(AstNode *p) 
{ 
  
   push_vs(p->SymbolNode);
}

// Times Statement
void ProcessTimesStmt(AstNode *p, int lev, int lvalue,int leftChild)
{ 
   symbol *lhs, *rhs, *wh;
   int TEMP_TAG_WHILE;
   TAG_WHILES++;
   TEMP_TAG_WHILE= TAG_WHILES;
   
   CodeGeneration(p->pAstNode[0],lev+1,0,0); 
   lhs = pop_vs();
   
   if(lhs->typos != INT){
	   
	   printf("Incompatible_Types_Error: The counter of times statement must be integer",lhs->typos);
	   exit(1);
	   
   }
   
   if( lhs->sclass == REGISTER ){
	   
	   /*Push a symbol to whiles stack, this helps 
	    'break' statements to recognize in which while-statement 
		they belong to */
		
	   wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);
	   
	   //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		 fprintf(text,"mov ecx, [rgs]\n");

		 //While definition
		 fprintf(text,"@WHILE_%d:\n",TEMP_TAG_WHILE);
		 
		 //Code Generation for the logical expression 
		 fprintf(text,"jcxz @ENDWHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"push ecx\n");
		 
         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
		 
		 fprintf(text,"pop ecx\n");
		 fprintf(text,"dec ecx\n");
		
		 fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
		 
		 pop_wh();
	  
   }
   else if( lhs->sclass == MEMORY ){
	   
	   /*Push a symbol to whiles stack, this helps 
	    'break' statements to recognize in which while-statement 
		they belong to */
		
	   wh = new_symbol("");
	   wh->timi = TEMP_TAG_WHILE;
	   push_wh(wh);
	   
	   //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		 fprintf(text,"mov ecx, [%s]\n",lhs->pseudonym);

		 //While definition
		 fprintf(text,"@WHILE_%d:\n",TEMP_TAG_WHILE);
		 
		 //Code Generation for the logical expression 
		 fprintf(text,"jcxz @ENDWHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"push ecx\n");
		 
         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
		 
		 fprintf(text,"pop ecx\n");
		 fprintf(text,"dec ecx\n");
		
		 fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
		 
		 pop_wh();
	  
   }
   else if( lhs->timi != 0 ){
		
		 wh = new_symbol("");
	     wh->timi = TEMP_TAG_WHILE;
	     push_wh(wh);
		 
		 //fprintf(data,"COUNTER_%d dd  %d\n",TEMP_TAG_WHILE,lhs->timi);
		 //fprintf(text,"mov ecx,[COUNTER_%d]\n",TEMP_TAG_WHILE);
		 fprintf(text,"mov ecx, %d\n",lhs->timi);

		 //While definition
		 fprintf(text,"@WHILE_%d:\n",TEMP_TAG_WHILE);
		 
		 //Code Generation for the logical expression 
		 fprintf(text,"jcxz @ENDWHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"push ecx\n");
		 
         CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
		 
		 fprintf(text,"pop ecx\n");
		 fprintf(text,"dec ecx\n");
		
		 fprintf(text,"jmp @WHILE_%d\n",TEMP_TAG_WHILE);
		 fprintf(text,"@ENDWHILE_%d:\n", TEMP_TAG_WHILE);
		 
		 pop_wh();
      }
     
   
   
   
   
}

// If Statement
 void ProcessIfStmt(AstNode*p,int lev, int lvalue,int leftChild){
	 
	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	 lhs = pop_vs();
	 
	 if(lhs->typos != BOOL){
	   
	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);
	   
    }
    
	 if( lhs->sclass == REGISTER ){
		 
		 TAG_IFS++;
		 TEMP_TAG_IF = TAG_IFS;
		 
		 fprintf(text,"mov ecx,[rgs]\n");
		 fprintf(text,"jcxz @ENDIF_%d\n",TEMP_TAG_IF);
		 
		 //Code Generation for true 
		 CodeGeneration(p->pAstNode[1],lev+1,lvalue,1); 
		
		 //End
		 fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		 
	    }
	else if( lhs->sclass == MEMORY ){
		   
		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;
		  
		  fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"jcxz @ENDIF_%d\n",TEMP_TAG_IF);
		  
		  //Code Generation for true 
		  CodeGeneration(p->pAstNode[1],lev+1,lvalue,1); 
		 
		   //End
		  fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		  
		  }
	else {
		  
		  if( lhs->timi != 0 ){
				
				CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
			  }
		
		  
		 }
		  
 }
 

// If-else Statement
 void ProcessIfElseStmt(AstNode*p,int lev, int lvalue,int leftChild){
	 
	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	 lhs = pop_vs();
	 
     if(lhs->typos != BOOL){
	   
	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);
	   
    }
   
	 if( lhs->sclass == REGISTER ){
		 
		 TAG_IFS++;
		 TEMP_TAG_IF = TAG_IFS;
		 
		 fprintf(text,"mov ecx,[rgs]\n");
		 fprintf(text,"jcxz @ELSE_%d\n",TEMP_TAG_IF);
		 
		 //Code Generation for true 
		 CodeGeneration(p->pAstNode[1],lev+1,lvalue,1); 
		 fprintf(text,"jmp @ENDIF_%d\n",TEMP_TAG_IF);
		 fprintf(text,"@ELSE_%d:\n", TEMP_TAG_IF);
		 
		 //Code Generation for false
		 CodeGeneration(p->pAstNode[2],lev+1,lvalue,1); 
		 
		 //End
		 fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		 
	    }
	else if( lhs->sclass == MEMORY ){
		   
		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;
		  
		  fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"jcxz @ELSE_%d\n",TEMP_TAG_IF);
		  
		  //Code Generation for true 
		  CodeGeneration(p->pAstNode[1],lev+1,lvalue,1); 
		  fprintf(text,"jmp @ENDIF_%d\n",TEMP_TAG_IF);
		  fprintf(text,"@ELSE_%d:\n", TEMP_TAG_IF);
		  
		  //Code Generation for false
		  CodeGeneration(p->pAstNode[2],lev+1,lvalue,1); 
		  
		   //End
		  fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		  
		  }
	else {
		  
		  if( lhs->timi != 0 ){
				
				CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
			  }
		  else{ 
				
				CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
				
			  }
		  
		 }
		  
 }
 
 // Single If Statement
 void ProcessSingleIfStmt(AstNode*p,int lev, int lvalue,int leftChild){
	 
	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	 lhs = pop_vs();
	 
	  if(lhs->typos != BOOL){
	   
	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);
	   
    }
    
	 if( lhs->sclass == REGISTER ){
		 
		 TAG_IFS++;
		 TEMP_TAG_IF = TAG_IFS;
		 
		 fprintf(text,"mov ecx,[rgs]\n");
		 fprintf(text,"jcxz @ENDIF_%d\n",TEMP_TAG_IF);
		 
		 //Code Generation for true 
		 CodeGeneration(p->pAstNode[0],lev+1,lvalue,1); 
		 
		 //End
		 fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		 
	    }
	else if( lhs->sclass == MEMORY ){
		   
		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;
		  
		  fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"jcxz @ENDIF_%d\n",TEMP_TAG_IF);
		  
		  //Code Generation for true 
		  CodeGeneration(p->pAstNode[0],lev+1,lvalue,1); 
		 
		   //End
		  fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		  
		  }
	else {
		  
		  if( lhs->timi != 0 ){
				
				CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
			  }
		 
		  
	 }
		  
 }
 
 // Single Unless Statement
 void ProcessSingleUnlessStmt(AstNode*p,int lev, int lvalue,int leftChild){
	 
	 symbol *lhs;
	 int TEMP_TAG_IF;
	 CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	 lhs = pop_vs();
	 
	 if(lhs->typos != BOOL){
	   
	   printf("Incompatible_Types_Error: %d cannot be converted to boolean",lhs->typos);
	   exit(1);
	   
   }
    
	 if( lhs->sclass == REGISTER ){
		 
		 TAG_IFS++;
		 TEMP_TAG_IF = TAG_IFS;
		 
		 fprintf(text,"mov ecx,[rgs]\n");
		 fprintf(text,"cmp ecx,0\n");
		 fprintf(text,"jne @ENDIF_%d\n",TEMP_TAG_IF);
		 
		 //Code Generation for true 
		 CodeGeneration(p->pAstNode[0],lev+1,lvalue,1); 
		 
		 //End
		 fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		 
	    }
	else if( lhs->sclass == MEMORY ){
		   
		  TAG_IFS++;
		  TEMP_TAG_IF = TAG_IFS;
		  
		  fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
		  fprintf(text,"cmp ecx,0\n");
		  fprintf(text,"jne @ENDIF_%d\n",TEMP_TAG_IF);
		  
		  //Code Generation for true 
		  CodeGeneration(p->pAstNode[0],lev+1,lvalue,1); 
		 
		   //End
		  fprintf(text,"@ENDIF_%d:\n",TEMP_TAG_IF);
		  
		  }
	else {
		  
		  if( lhs->timi == 0 ){
				
				CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
			  }
		 
		  
	 }
		  
 }
 

 
 //Assign Statement
void ProcessAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
 
   lhs = pop_vs();
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();
 
   switch(lhs->sclass) 
	   {
		  case MEMORY:
		  
			  switch(lhs->typos){
				  
					case INT:
					
							 switch(rhs->typos){
								 
									case INT:
											 if(rhs->sclass == MEMORY){
												 
													if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
														
														fprintf(text,"mov eax,[%s]\n",rhs->pseudonym);
														fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
														
													}
												   
												 }
											 else if(rhs->sclass == CONSTANT) {
												 
													fprintf(text,"mov eax,%d\n",rhs->timi);
													fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
													
												   
												 }
											 else if(rhs->sclass == REGISTER)      
												 {
													fprintf(text,"mov eax,[rgs]\n");
													fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
													
													
													
												 }
											else {  /*---- STACK ---*/
												
												 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
											 }
									break;
									case REAL:
													 if(rhs->sclass == MEMORY){
														 
															fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
															//fprintf(text,"fldcw [cw]\n");
															fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
																
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"fld qword [frgs]\n");
															//fprintf(text,"fldcw [cw]\n");
															fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
							 }
					break;							 
					case REAL:
					
							switch(rhs->typos){
										 
											case INT:
													 if(rhs->sclass == MEMORY){
														 
															fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
																
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"fild dword [rgs]\n");
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
											break;
											case REAL:
													 if(rhs->sclass == MEMORY){
														 
															fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"fld qword [frgs]\n");
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
											break;
											case BOOL:
												printf("Error: bad operand types for binary operator \n");
												exit(1);
											break;
									 }
					break;
					case BOOL:
					
					   switch(rhs->typos){
								case INT:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								case REAL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								case BOOL:
													 if(rhs->sclass == MEMORY){
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																fprintf(text,"mov eax,[%s]\n",rhs->pseudonym);
																fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
															fprintf(text,"mov eax,%d\n",rhs->timi);
															fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
															
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"mov eax,[rgs]\n");
															fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
															
															
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
								break;
					   }
					   
					break;
			    }
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ASSIGN[STACK-]");
		  break;
	   }
	
	push_vs(lhs);
	push_vs(rhs);

}

void ProcessUniqueAssign(AstNode*p, int lev,int leftChild){
	
	symbol *lhs , *rhs; 
	
	ProcessAssign(p,lev,leftChild);
	rhs = pop_vs();
	lhs = pop_vs();
	
	switch(rhs->typos){
		
		case INT:
				switch(lhs->typos){
					
					case INT:
						//Nothing to pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
		
		break;
		case REAL:	
			switch(lhs->typos){
					
					case INT:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
			
		break;
		case BOOL:
				switch(lhs->typos){
					
					case INT:
						//Nothing to pop
					break;
					case REAL:
						//Nothing to pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
		
		break;
		
		
	}
	
	
}
 
 

//Add Assign Statement
void ProcessAddAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();
   
  
   switch(lhs->sclass) 
	   {
		  case MEMORY:
				switch(lhs->typos) {
					
					case INT:
							switch(rhs->typos){
								
								case INT:
										 if(rhs->sclass == MEMORY){
											 
												
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"add eax,[%s]\n",rhs->pseudonym);
													fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
												
											   
											 }
										 else if(rhs->sclass == CONSTANT) {
											 
												fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												fprintf(text,"add eax,%d\n",rhs->timi);
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
											   
											 }
										 else if(rhs->sclass == REGISTER)      
											 {
												fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												fprintf(text,"add eax,[rgs]\n");
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
												
											 }
										else {  /*---- STACK ---*/
											
											 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
										 }
								break;
								case REAL:
								
									                if(rhs->sclass == MEMORY){
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
																fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
													          //  fprintf(text,"fldcw [cw]\n");
																fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fadd qword [frgs]\n");
													       // fprintf(text,"fldcw [cw]\n");
															fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
								break;
								case BOOL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
							}
					break;
					case REAL:
					
						switch(rhs->typos){
									
									case INT:
											 if(rhs->sclass == MEMORY){
												 
													 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													 fprintf(text,"fiadd dword [%s]\n",rhs->pseudonym);
													 fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											 else if(rhs->sclass == CONSTANT) {
												 
													 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
													 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													 fprintf(text,"fiadd dword [INT_%d]\n",NUM_OF_INT_CONST++);
												 
													
													 fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
												   
												 }
											 else if(rhs->sclass == REGISTER)      
												 {
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fiadd dword [rgs]\n");
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											else {  /*---- STACK ---*/
												
												 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
											 }
									break;
									case REAL:
											 if(rhs->sclass == MEMORY){
												 
														fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
														fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
														fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
														
												 }
											 else if(rhs->sclass == CONSTANT) {
												 
													fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
													
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
												 
												   
												 }
											 else if(rhs->sclass == REGISTER)      
												 {
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fadd qword [frgs]\n");
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											else {  /*---- STACK ---*/
												
												 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
											 }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
								}
					break;
					case BOOL:
							printf("Error: bad operand types for binary operator \n");
							exit(1);
					break;
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ADDASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ADDASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ADDASSIGN[STACK-]");
		  break;
	   }
	   


}

//Sub Assign Statement
void ProcessSubAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();
   
  
   switch(lhs->sclass) 
	   {
		  case MEMORY:
				switch(lhs->typos) {
					
					case INT:
							switch(rhs->typos){
								
								case INT:
										 if(rhs->sclass == MEMORY){
											 
												
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"sub eax,[%s]\n",rhs->pseudonym);
													fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
												
											   
											 }
										 else if(rhs->sclass == CONSTANT) {
											 
												fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												fprintf(text,"sub eax,%d\n",rhs->timi);
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
											   
											 }
										 else if(rhs->sclass == REGISTER)      
											 {
												fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												fprintf(text,"sub eax,[rgs]\n");
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
												
											 }
										else {  /*---- STACK ---*/
											
											 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
										 }
								break;
								case REAL:
								
									                if(rhs->sclass == MEMORY){
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
																fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
													            //fprintf(text,"fldcw [cw]\n");
																fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fsub qword [frgs]\n");
													       // fprintf(text,"fldcw [cw]\n");
															fprintf(text,"fistp dword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
								break;
								case BOOL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
							}
					break;
					case REAL:
					
						switch(rhs->typos){
									
									case INT:
											 if(rhs->sclass == MEMORY){
												 
													 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													 fprintf(text,"fisub dword [%s]\n",rhs->pseudonym);
													 fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											 else if(rhs->sclass == CONSTANT) {
												 
													 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
													 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													 fprintf(text,"fisub dword [INT_%d]\n",NUM_OF_INT_CONST++);
												 
													
													 fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
												   
												 }
											 else if(rhs->sclass == REGISTER)      
												 {
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fisub dword [rgs]\n");
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											else {  /*---- STACK ---*/
												
												 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
											 }
									break;
									case REAL:
											 if(rhs->sclass == MEMORY){
												 
														fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
														fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
														fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
														
												 }
											 else if(rhs->sclass == CONSTANT) {
												 
													fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
													
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
												 
												   
												 }
											 else if(rhs->sclass == REGISTER)      
												 {
													fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
													fprintf(text,"fsub qword [frgs]\n");
													fprintf(text,"fstp qword [%s]\n",lhs->pseudonym);
													
												 }
											else {  /*---- STACK ---*/
												
												 fprintf(text,"ERROR ADDASSIGN[MEMORY-STACK]");
											 }
									break;
									case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
								}
					break;
					case BOOL:
							printf("Error: bad operand types for binary operator \n");
							exit(1);
					break;
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ADDASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ADDASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ADDASSIGN[STACK-]");
		  break;
	   }


}

//Increase after 
void ProcessIncreaseAfter(AstNode* p, int lev, int leftChild){
	
	symbol *lhs;
	
	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();
	
	
	if (leftChild == 1){
		
		lhs->sclass = STACK;
		
		fprintf(text, "mov  eax, [%s]\n", lhs->pseudonym);
		fprintf(text, "push eax\n");
		fprintf(text, "inc  eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		
	} else {
	
		lhs->sclass = REGISTER;
		
		fprintf(text, "mov eax,[%s]\n", lhs->pseudonym);
		fprintf(text, "mov dword [rgs],eax\n");
		fprintf(text, "inc eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
	
	}
	
	push_vs(lhs);
	
}

//Increase Before
void ProcessIncreaseBefore(AstNode* p, int lev, int leftChild){
	
	symbol *lhs;
	
	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();
	
	
	if (leftChild == 1){
		
		lhs->sclass = STACK;
		
		fprintf(text, "mov  eax, [%s]\n", lhs->pseudonym);
		fprintf(text, "inc  eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		fprintf(text, "push eax\n");
		
		
	} else {
	
		lhs->sclass = REGISTER;
		
		fprintf(text, "mov eax,[%s]\n", lhs->pseudonym);
		fprintf(text, "inc eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		fprintf(text, "mov dword [rgs],eax\n");
		
	
	}
	
	push_vs(lhs);
	
}

//Decrease after 
void ProcessDecreaseAfter(AstNode* p, int lev, int leftChild){
	
	symbol *lhs;
	
	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();
	
	
	if (leftChild == 1){
		
		lhs->sclass = STACK;
		
		fprintf(text, "mov  eax, [%s]\n", lhs->pseudonym);
		fprintf(text, "push eax\n");
		fprintf(text, "dec  eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		
	} else {
	
		lhs->sclass = REGISTER;
		
		fprintf(text, "mov eax,[%s]\n", lhs->pseudonym);
		fprintf(text, "mov dword [rgs],eax\n");
		fprintf(text, "dec eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
	
	}
	
	push_vs(lhs);
	
}


//Decrease Before
void ProcessDecreaseBefore(AstNode* p, int lev, int leftChild){
	
	symbol *lhs;
	
	CodeGeneration(p->pAstNode[0],lev+1,0,0); // Location
	lhs = pop_vs();
	
	
	if (leftChild == 1){
		
		lhs->sclass = STACK;
		
		fprintf(text, "mov  eax, [%s]\n", lhs->pseudonym);
		fprintf(text, "dec  eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		fprintf(text, "push eax\n");
		
		
	} else {
	
		lhs->sclass = REGISTER;
		
		fprintf(text, "mov eax,[%s]\n", lhs->pseudonym);
		fprintf(text, "dec eax\n");
		fprintf(text, "mov dword [%s],eax\n", lhs->pseudonym);
		fprintf(text, "mov dword [rgs],eax\n");
		
	
	}
	
	push_vs(lhs);
	
}




//Assign Sequence Statement
void ProcessAssignSeq(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
 
   //Code Generation for assign-expression(right)
   if(p->pAstNode[1] ->NodeType == astAssign)
		ProcessAssign(p->pAstNode[1],lev+1,0);
   else if(p->pAstNode[1]->NodeType == astAssignSeq)
		ProcessAssignSeq(p->pAstNode[1],lev+1,0);
	
   rhs = pop_vs();
   
   pop_vs(); // pop the lhs of assign
  
   switch(lhs->sclass) 
	   {
		  case MEMORY:
		  
				switch(lhs->typos){
					
					case INT:
					
						switch(rhs->typos){
							
							case INT:
									 if(rhs->sclass == MEMORY){
										 
											if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
												
												fprintf(text,"mov eax,[%s]\n",rhs->pseudonym);
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
												
											}
										   
										 }
									 else if(rhs->sclass == CONSTANT) {
										 
											fprintf(text,"mov eax,%d\n",rhs->timi);
											fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
										   
										 }
									 else if(rhs->sclass == REGISTER)      
										 {
											fprintf(text,"mov eax,[rgs]\n");
											fprintf(text,"mov [%s],eax\n",lhs->pseudonym);  
											
										 }
									else {  /*---- STACK ---*/
										
										 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									 }
							break;
							case REAL:
							
									if(rhs->sclass == MEMORY){
															 
											if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																	
													//fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
													//fprintf(text,"fldcw [cw]\n");
													fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
																	
													}
															   
									 }
									else if(rhs->sclass == CONSTANT) {
															 
											//fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,(int)rhs->dtimi);
											//fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
											fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
															   
									}
									else if(rhs->sclass == REGISTER){
										
											//fprintf(text,"fld qword [frgs]\n");
											//fprintf(text,"fldcw [cw]\n");
											fprintf(text,"fist dword [%s]\n",lhs->pseudonym);
																
									}
									else {  /*---- STACK ---*/
															
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													
									}
							break;
							case BOOL:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
						}
					break;
					case REAL:
					
							switch(rhs->typos){
										 
											case INT:
													 if(rhs->sclass == MEMORY){
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																//fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
																fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    //fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															//fprintf(text,"fild dword [INT_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															//fprintf(text,"fild dword [rgs]\n");
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
											break;
											case REAL:
													 if(rhs->sclass == MEMORY){
														 
															if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
																
																//fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
																fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
																
															}
														   
														 }
													 else if(rhs->sclass == CONSTANT) {
														 
														    //fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															//fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
														   
														 }
													 else if(rhs->sclass == REGISTER)      
														 {
															//fprintf(text,"fld qword [frgs]\n");
															fprintf(text,"fst qword [%s]\n",lhs->pseudonym);
															
														 }
													else {  /*---- STACK ---*/
														
														 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
													 }
											break;
											case BOOL:
												printf("Error: bad operand types for binary operator \n");
												exit(1);
											break;
									 }
					break;
					case BOOL:
					
						switch(rhs->typos){
							
							case BOOL:
									 if(rhs->sclass == MEMORY){
										 
											if( strcmp(lhs->pseudonym,rhs->pseudonym) != 0 ) {
												
												fprintf(text,"mov eax,[%s]\n",rhs->pseudonym);
												fprintf(text,"mov [%s],eax\n",lhs->pseudonym);
												
											}
										   
										 }
									 else if(rhs->sclass == CONSTANT) {
										 
											fprintf(text,"mov eax,%d\n",rhs->timi);
											fprintf(text,"mov [%s],eax\n",lhs->pseudonym); 
										   
										 }
									 else if(rhs->sclass == REGISTER)      
										 {
											fprintf(text,"mov eax,[rgs]\n");
											fprintf(text,"mov [%s],eax\n",lhs->pseudonym);  
											
										 }
									else {  /*---- STACK ---*/
										
										 fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									 }
							break;
							case REAL:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
							case INT:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
						}
					break;
				}
		  break;
		  case CONSTANT:
			 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
		  break;
		  case REGISTER:
			 fprintf(text,"ERROR ASSIGN[REGISTER-]");
		  break;
		  case STACK:
			 fprintf(text,"ERROR ASSIGN[STACK-]");
		  break;
	   }
   
    push_vs(lhs);
    push_vs(rhs);
  
}

void ProcessAboveMultiAssignSeq(AstNode*p, int lev,int leftChild){
	
	symbol *lhs , *rhs; 
	
	ProcessAssignSeq(p,lev,leftChild);
	rhs = pop_vs();
	lhs = pop_vs();
	
	switch(rhs->typos){
		
		case INT:
				switch(lhs->typos){
					
					case INT:
						//Nothing to pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
		
		break;
		case REAL:	
			switch(lhs->typos){
					
					case INT:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case REAL:
						fprintf(text,"ffreep\n"); //free fsp and pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
			
		break;
		case BOOL:
				switch(lhs->typos){
					
					case INT:
						//Nothing to pop
					break;
					case REAL:
						//Nothing to pop
					break;
					case BOOL:
						//Nothing to pop
					break;
				}
		
		break;
		
		
	}
	
	
}

//Listed Assign Statement
void ProcessListedAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
  
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;
   
   //Code Generation for nested
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
  
   
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[2],lev+1,0,0);
   rhs = pop_vs();
   
   
  
   switch(lhs->sclass) 
	   {
		  case MEMORY:
		  
					 switch(rhs->typos){
										
							case INT:
									r_types[R_TYPES_COUNTER++] = INT;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;		
							case REAL:
								
									r_types[R_TYPES_COUNTER++] = REAL;
									
									fprintf(text,"sub esp,8\n");
								
									if(rhs->sclass == MEMORY){
										
										fprintf(text,"fld qword [%s]\n",rhs->pseudonym);				 
										fprintf(text,"fstp qword [esp]\n");
														
										}
													
									else if(rhs->sclass == CONSTANT) {
										
										fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
										fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);				 
										fprintf(text,"fstp qword [esp]\n");
											
											
									}			
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"fld qword [frgs]\n");				 
										fprintf(text,"fstp qword [esp]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
								
							
							break;
							case BOOL:
									r_types[R_TYPES_COUNTER++] = BOOL;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;
					 }
								 
				  break;
				  case CONSTANT:
					 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
				  break;
				  case REGISTER:
					 fprintf(text,"ERROR ASSIGN[REGISTER-]");
				  break;
				  case STACK:
					 fprintf(text,"ERROR ASSIGN[STACK-]");
				  break;
			   
	   }
	   
	   int i;
	   R_TYPES_COUNTER--;
	   
	   for (i = LOC_ASSIGN_COUNTER-1; i >= 0; i--){
			
			
			switch(assigns[i]->typos){
				
				
				case INT:
				
						switch(r_types[R_TYPES_COUNTER--]){
							
							case INT:
								fprintf(text, "pop  eax\n");
								fprintf(text, "mov  dword [%s], eax\n",  assigns[i]->pseudonym);
							break;
							case REAL:
								printf("Προσοχή: Ο τύπος της μεταβλητής '%s' δεν είναι 'real'\n",assigns[i]->name);
								fprintf(text, "fld qword [esp]\n");
								fprintf(text, "add  esp,8\n");
								//fprintf(text,"fldcw [cw]\n");
								fprintf(text, "fistp dword [%s]\n",  assigns[i]->pseudonym);
							
							break;
							case BOOL:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
							
						}
				
				break;
				case REAL:
				
					switch(r_types[R_TYPES_COUNTER--]){
								
								case INT:
									fprintf(text, "fild dword [esp]\n");
									fprintf(text, "add  esp,4\n");
									fprintf(text, "fstp qword [%s]\n",  assigns[i]->pseudonym);
								break;
								case REAL:
									
									fprintf(text, "fld qword [esp]\n");
									fprintf(text, "add  esp,8\n");
									fprintf(text, "fstp qword [%s]\n",  assigns[i]->pseudonym);
								
								break;
								case BOOL:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								
							}
				break;
				case BOOL:
				
						switch(r_types[R_TYPES_COUNTER--]){
							
							case BOOL:
								fprintf(text, "pop  eax\n");
								fprintf(text, "mov  dword [%s], eax\n",  assigns[i]->pseudonym);
							break;
							case REAL:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
							case INT:
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							break;
							
						}
				
				break;
			
				
			}
			
			
			
		}
		
	   R_TYPES_COUNTER = 0; // Already is zero
	   LOC_ASSIGN_COUNTER =0;
	   
	   
	   
 } 





//Nested Assign Statement
void ProcessNestedAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;
   
   //Code Generation for nested
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   
   
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[2],lev+1,0,0);
   rhs = pop_vs();
   
   
   
  
   switch(lhs->sclass) 
	   {
		  case MEMORY:
		  
					 switch(rhs->typos){
										
							case INT:
									r_types[R_TYPES_COUNTER++] = INT;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;		
							case REAL:
								
									r_types[R_TYPES_COUNTER++] = REAL;
									
									fprintf(text,"sub esp,8\n");
								
									if(rhs->sclass == MEMORY){
										
										fprintf(text,"fld qword [%s]\n",rhs->pseudonym);				 
										fprintf(text,"fstp qword [esp]\n");
														
										}
													
									else if(rhs->sclass == CONSTANT) {
										
										fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
										fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);				 
										fprintf(text,"fstp qword [esp]\n");
											
											
									}			
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"fld qword [frgs]\n");				 
										fprintf(text,"fstp qword [esp]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
								
							
							break;
							case BOOL:
									r_types[R_TYPES_COUNTER++] = BOOL;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;
					 }
								 
				  break;
				  case CONSTANT:
					 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
				  break;
				  case REGISTER:
					 fprintf(text,"ERROR ASSIGN[REGISTER-]");
				  break;
				  case STACK:
					 fprintf(text,"ERROR ASSIGN[STACK-]");
				  break;
			   
	   }
	   

}


 //Embed Assign Statement
void ProcessEmbedAssign(AstNode*p, int lev,int leftChild){	

   symbol *rhs,*lhs;
   
   //Code Generation for location(left)
   CodeGeneration(p->pAstNode[0],lev+1,1,0);
   lhs = pop_vs();
   assigns[LOC_ASSIGN_COUNTER++] = lhs;
  
   //Code Generation for expression(right)
   CodeGeneration(p->pAstNode[1],lev+1,0,0);
   rhs = pop_vs();
   
   
  
    switch(lhs->sclass) 
	   {
		  case MEMORY:
		  
					 switch(rhs->typos){
										
							case INT:
									r_types[R_TYPES_COUNTER++] = INT;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;		
							case REAL:
								
									r_types[R_TYPES_COUNTER++] = REAL;
									
									fprintf(text,"sub esp,8\n");
								
									if(rhs->sclass == MEMORY){
										
										fprintf(text,"fld qword [%s]\n",rhs->pseudonym);				 
										fprintf(text,"fstp qword [esp]\n");
														
										}
													
									else if(rhs->sclass == CONSTANT) {
										
										fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
										fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);				 
										fprintf(text,"fstp qword [esp]\n");
											
											
									}			
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"fld qword [frgs]\n");				 
										fprintf(text,"fstp qword [esp]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
								
							
							break;
							case BOOL:
									r_types[R_TYPES_COUNTER++] = BOOL;
									
									if(rhs->sclass == MEMORY){
														 
										fprintf(text,"push dword [%s]\n",rhs->pseudonym);
														
										}
													
									else if(rhs->sclass == CONSTANT) {
														 
										fprintf(text,"push %d\n",rhs->timi);
															
										}
													
									else if(rhs->sclass == REGISTER){
															
										fprintf(text,"mov dword [rgs]\n");
															  
									}
									else {  /*---- STACK ---*/
											
											fprintf(text,"ERROR ASSIGN[MEMORY-STACK]");
									}
										
							break;
					 }
								 
				  break;
				  case CONSTANT:
					 fprintf(text,"ERROR ASSIGN[CONSTANT-]");
				  break;
				  case REGISTER:
					 fprintf(text,"ERROR ASSIGN[REGISTER-]");
				  break;
				  case STACK:
					 fprintf(text,"ERROR ASSIGN[STACK-]");
				  break;
			   
	   }
	   

}

//Location
void ProcessLocation(AstNode* p){	
    
	/*symbol *sn;
	
	sn = new_symbol(p->SymbolNode->name);
    strcpy(sn->pseudonym,p->SymbolNode->pseudonym);
	sn->lvalue = 0;
	sn->sclass = MEMORY;*/
	
	push_vs(p->SymbolNode);

}

//Not Expression
void ProcessNotExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  

   symbol *lhs;
   
   //Code Generation for right operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,leftChild);
   lhs=pop_vs();
   
   if(lhs->typos != BOOL){
	   
	   printf("Logical_Error: Bad operand type for unary operator 'not'");
	   exit(1);
	   
   }
	   
  
   switch(lhs->sclass) 
   {
      case MEMORY:
		
			fprintf(text,"mov ecx,[%s]\n",lhs->pseudonym);
			fprintf(text,"mov  eax, 1\n");
			fprintf(text,"jcxz $ + 8\n");
			fprintf(text,"mov  eax, 0\n");	
			
			if (leftChild == 1){
				fprintf(text, "push eax\n");
				lhs->sclass = STACK;				
			} else {
				fprintf(text, "mov [rgs], eax\n");	
				lhs->sclass = REGISTER;
			}
			
      break;
      case REGISTER:
            fprintf(text,"mov ecx,[rgs]\n");
			fprintf(text,"mov  eax, 1\n");
			fprintf(text,"jcxz $ + 8\n");
			fprintf(text,"mov  eax, 0\n");
			fprintf(text,"mov [rgs],eax\n");
			
      break;
      case CONSTANT:
	  
			 lhs->timi = !lhs->timi;
      break;
      case STACK:
       		
				// -- POP -- //
				fprintf(text,"pop ecx\n");
				fprintf(text,"mov  eax, 1\n");
				fprintf(text,"jcxz $ + 8\n");
				fprintf(text,"mov  eax, 0\n");	
				fprintf(text,"push eax\n");		   
				
        
      break;
   }
  
 	   
	push_vs(lhs);
}   

//And Expression
void ProcessAndExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  

   symbol *sn,*rhs,*lhs;
   
   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();
   
   //Code Generation for right operand
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
   rhs=pop_vs();
   
   if(lhs->typos != BOOL || rhs->typos != BOOL){
	   
	   printf("Logical_Error: Bad operand types for binary operator 'and'");
	   exit(1);
	   
   }
   
   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos=BOOL;
   sn->sclass=REGISTER;
   
   
   switch(lhs->sclass) 
   {
      case MEMORY:
	  
			fprintf(text, "mov eax, 0\n");
			fprintf(text, "mov ecx, [%s]\n", lhs->pseudonym);
			
			 if(rhs->sclass == MEMORY) {
				
				fprintf(text, "jcxz $ + 14\n");
				fprintf(text,"mov ecx,[%s]\n", rhs->pseudonym);
				
			 }
			 else if(rhs->sclass == CONSTANT){
				 
				fprintf(text,"jcxz $ + 16\n"); // jump 3 statements later (2+5+3=10)
				fprintf(text,"mov ecx,%d\n", rhs->timi);
				
			 }
			 else if (rhs->sclass == REGISTER){
				 
				fprintf(text, "jcxz $ + 17\n"); // jump 3 statements later (2+6+3=11)
				fprintf(text, "mov ecx,[rgs]\n");
				
			 } 
			 else{ /* -- STACK -- */
			    fprintf(text,"ERROR LOGEXPR(MEMORY-STACK)\n");
			}
      break;
      case REGISTER:
         fprintf(text,"ERROR LOGEXPR[REGISTER-]");
      break;
      case CONSTANT:
	  
			 if(rhs->sclass == REGISTER){
				 
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         
				 fprintf(text,"jcxz $ + 17\n");
				 fprintf(text, "mov ecx,[rgs]\n");
			  
			 }
			 else if(rhs->sclass == CONSTANT)
			 {
				 
					sn->timi = (lhs->timi && rhs->timi);
					
				    sn->sclass = CONSTANT; 
				
			 }
			 else if(rhs->sclass == MEMORY){
				  
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         
				 fprintf(text,"jcxz $ + 14\n");
				 fprintf(text, "mov ecx,[%s]\n",rhs->pseudonym);
				  
			 }
			 else{ /* -- STACK -- */
				
				  fprintf(text,"ERROR LOGEXPR[CONSTANT-STACK]\n");			
			}
      break;
      case STACK:
       		
				// -- POP -- //
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "pop ecx\n");
		        
				
					   
				if(rhs->sclass == MEMORY){
						   
					 fprintf(text,"jcxz $ + 14\n");
					 fprintf(text,"mov ecx,[%s]\n",rhs->pseudonym);
					
				 }
				else if (rhs->sclass == REGISTER) {
							  
					 fprintf(text,"jcxz $ + 17\n");
					 fprintf(text,"mov ecx,[rgs]\n");
							  
				 }
				else if(rhs->sclass == CONSTANT)  {
							   
					 fprintf(text,"jcxz $ + 16\n"); // jump 3 statements later (2+5+3=10)
					 fprintf(text,"mov ecx,%d\n", rhs->timi);
					
			     }
				else { /* -- STACK -- */
				   fprintf(text,"ERROR LOGEXPR[STACK-STACK]\n");				
			     }
        
      break;
   }
  
 
	if(sn->sclass == REGISTER ) 
		 {
			 fprintf(text, "jcxz $ + 8\n"); // jump 2 statements later
		     fprintf(text,"mov eax, 1\n");
			 
			if (leftChild == 1){
				
				         // -- PUSH -- //
						 fprintf(text,"push eax\n");
						
						
						  sn->sclass=STACK;
			}else {
				
				fprintf(text,"mov [rgs],eax\n");
				
			}
	}
			   
	push_vs(sn);
}   



//Or Expression
void ProcessOrExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  

   symbol *sn,*rhs,*lhs;
   
   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();
   
   //Code Generation for right operand
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
   rhs=pop_vs();
   
    if(lhs->typos != BOOL || rhs->typos != BOOL){
	   
	   printf("Logical_Error: Bad operand types for binary operator 'or'");
	   exit(1);
	   
   }
   
   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos=BOOL;
   sn->sclass=REGISTER;
   
   
   switch(lhs->sclass) 
   {
      case MEMORY:
	  
			fprintf(text, "mov eax, 0\n");
			fprintf(text, "mov ecx, [%s]\n", lhs->pseudonym);
			fprintf(text, "cmp ecx, 0\n");
			
			 if(rhs->sclass == MEMORY) {
				
				fprintf(text,"jne $ + 8\n");
				fprintf(text,"mov ecx, [%s]\n", rhs->pseudonym);
				
			 }
			 else if(rhs->sclass == CONSTANT){
				 
				fprintf(text, "jne $ + 10\n"); // jump 3 statements later (2+5+3=10)
				fprintf(text,"mov ecx,%d\n", rhs->timi);
				
			 }
			 else if (rhs->sclass == REGISTER){
				 
				fprintf(text, "jne $ + 11\n"); // jump 3 statements later (2+6+3=11)
				fprintf(text, "mov ecx,[rgs]\n");
				
			 } 
			 else{ /* -- STACK -- */
			    fprintf(text,"ERROR LOGEXPR(MEMORY-STACK)\n");
			}
      break;
      case REGISTER:
         fprintf(text,"ERROR LOGEXPR[REGISTER-]");
      break;
      case CONSTANT:
	  
			 if(rhs->sclass == REGISTER){
				 
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         fprintf(text, "cmp ecx, 0\n");
				 
				 fprintf(text,"jne $ + 11\n");
				 fprintf(text, "mov ecx,[rgs]\n");
			  
			 }
			 else if(rhs->sclass == CONSTANT)
			 {
				 
					sn->timi = (lhs->timi || rhs->timi);
					
				    sn->sclass = CONSTANT; 
				
			 }
			 else if(rhs->sclass == MEMORY){
				  
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "mov ecx, %d\n", lhs->pseudonym);
		         fprintf(text, "cmp ecx, 0\n");
				 
				 fprintf(text,"jne $ + 8\n");
				 fprintf(text, "mov ecx,[%s]\n",rhs->pseudonym);
				  
			 }
			 else{ /* -- STACK -- */
				
				  fprintf(text,"ERROR LOGEXPR[CONSTANT-STACK]\n");			
			}
      break;
      case STACK:
       		
				// -- POP -- //
				 fprintf(text, "mov eax, 0\n");
				 fprintf(text, "pop ecx\n");
		         fprintf(text, "cmp ecx, 0\n");
				
					   
				if(rhs->sclass == MEMORY){
						   
					 fprintf(text,"jne $ + 8\n");
					 fprintf(text,"mov ecx,[%s]\n",rhs->pseudonym);
					
				 }
				else if (rhs->sclass == REGISTER) {
							  
					 fprintf(text,"jne $ + 11\n");
					 fprintf(text,"mov ecx,[rgs]\n");
							  
				 }
				else if(rhs->sclass == CONSTANT)  {
							   
					 fprintf(text, "jne $ + 10\n"); // jump 3 statements later (2+5+3=10)
					 fprintf(text,"mov ecx,%d\n", rhs->timi);
					
			     }
				else { /* -- STACK -- */
				   fprintf(text,"ERROR LOGEXPR[STACK-STACK]\n");				
			     }
        
      break;
   }
  
 
	if(sn->sclass == REGISTER ) 
		 {
			 fprintf(text, "jcxz $ + 8\n"); // jump 2 statements later
		     fprintf(text,"mov eax, 1\n");
			 
			if (leftChild == 1){
				
				         // -- PUSH -- //
						 fprintf(text,"push eax\n");
						
						
						  sn->sclass=STACK;
			}else {
				
				fprintf(text,"mov [rgs],eax\n");
				
			}
	}
			   
	push_vs(sn);
}   


//Compare Expression
void ProcessCompExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  

   symbol *sn,*rhs,*lhs;
   
   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();
   
   //Code Generation for right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();
   
   sn=new_symbol("");
   sn->lvalue = 0;
   sn->typos= BOOL;
   sn->sclass=REGISTER;

   
   switch(lhs->sclass) 
   {
      case MEMORY:
			
				switch(lhs->typos){
							
							case INT:
								 switch(rhs->typos){
									 
									 
									 case INT:
												 if(rhs->sclass == MEMORY) {
							
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,%d\n",rhs->timi);
													
												 }
												 else if (rhs->sclass == REGISTER){
													 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[rgs]\n");
													
												 } 
												 else{ /* -- STACK -- */
													fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
												}
									 
									 
									 break;
									 case REAL:
									 
											     if(rhs->sclass == MEMORY) {
							
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
													
													fprintf(text,"fcomip\n");
													fprintf(text,"ffreep\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);		
													
													fprintf(text,"fcomip\n");
													fprintf(text,"ffreep\n");
													
												 }
												 else if (rhs->sclass == REGISTER){
													 
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fld qword [frgs]\n");
													
													fprintf(text,"fcomip\n");
													fprintf(text,"ffreep\n");
													
												 } 
												 else{ /* -- STACK -- */
													fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
												}
									 
									 break;
									 case BOOL:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									 break;
									 
								 }
							
							break;
							case REAL:
							
										switch(rhs->typos){
												 
												 
												 case INT:
															  if(rhs->sclass == MEMORY) {
							
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 }
															 else if(rhs->sclass == CONSTANT){
																 
																fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);		
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 }
															 else if (rhs->sclass == REGISTER){
																 
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fild dword [rgs]\n");
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 } 
															 else{ /* -- STACK -- */
																fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
															}
												 
												 
												 break;
												 case REAL:
												 
															 if(rhs->sclass == MEMORY) {
										
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 }
															 else if(rhs->sclass == CONSTANT){
																 
																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);		
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 }
															 else if (rhs->sclass == REGISTER){
																 
																fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																fprintf(text,"fld qword [frgs]\n");
																
																fprintf(text,"fcomip\n");
																fprintf(text,"ffreep\n");
																
															 } 
															 else{ /* -- STACK -- */
																fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
															}
												 
												 break;
												 case BOOL:
													printf("Error: bad operand types for binary operator \n");
													exit(1);
												 break;
												 
											 }
							
							break;
							case BOOL:
								 
								 switch(rhs->typos){
									 
									 
									 case BOOL:
												 //check for == and !=
									 
									 
												 if(rhs->sclass == MEMORY) {
							
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,%d\n",rhs->timi);
													
												 }
												 else if (rhs->sclass == REGISTER){
													 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"cmp eax,[rgs]\n");
													
												 } 
												 else{ /* -- STACK -- */
													fprintf(text,"ERROR COMPEXPR(MEMORY-STACK)\n");
												}
									 
									 
									 break;
									 case REAL:
									 
										printf("Error: bad operand types for binary operator \n");
										exit(1);
											
									 break;
									 case INT:
									 
										printf("Error: bad operand types for binary operator \n");
										exit(1);
										
									 break;
									 
								 }
							
							break;
					  
						}
							
	  
      break;
      case REGISTER:
         fprintf(text,"ERROR COMPEXPR[REGISTER-]");
      break;
      case CONSTANT:
	  
				switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 
									 case INT:
									 
											 if(rhs->sclass == REGISTER){
					 
												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[rgs]\n");
											  
											 }
											 else if(rhs->sclass == CONSTANT)
											 {
												 
												 switch (p->pAstNode[1]->NodeType){
													 
														case astLeOp:
															sn->timi = (lhs->timi <= rhs->timi);
															
														break;
														case astLOp:
															sn->timi  = (lhs->timi < rhs->timi);					
														break;
														case astGOp:
															sn->timi  = (lhs->timi > rhs->timi);					
														break;
														case astGeOp:
															sn->timi = (lhs->timi >= rhs->timi);					
														break;
														case astEOp:
															sn->timi = (lhs->timi == rhs->timi);					
														break;
														case astNeOp:
															sn->timi = (lhs->timi != rhs->timi);					
														break;
													}
												
												sn->sclass = CONSTANT; 
											 }
											 else if(rhs->sclass == MEMORY){
												  
												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
												  
											 }
											 else{ /* -- STACK -- */
												
												  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");			
											}
									 break;
									 case REAL:
									 
										         if(rhs->sclass == REGISTER){
													 
													  fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													  fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);	
													  fprintf(text,"fld qword [frgs]\n");
													  
													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");
													  
												 }
												 else if(rhs->sclass == CONSTANT)
												 {
													 
													 switch (p->pAstNode[1]->NodeType){
														 
															case astLeOp:
															
																sn->timi = (lhs->timi <= rhs->dtimi);
																
															break;
															case astLOp:
															
																sn->timi  = (lhs->timi < rhs->dtimi);		
																
															break;
															case astGOp:
															
																sn->timi  = (lhs->timi > rhs->dtimi);	
																
															break;
															case astGeOp:
															
																sn->timi = (lhs->timi >= rhs->dtimi);		
																
															break;
															case astEOp:
															
																sn->timi = (lhs->timi == rhs->dtimi);		
																
															break;
															case astNeOp:
															
																sn->timi = (lhs->timi != rhs->dtimi);	
																
															break;
														}
													
													sn->sclass = CONSTANT; 
												 }
												 else if(rhs->sclass == MEMORY){
													  
													  fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													  fprintf(text,"fild dword [INT_%d]\n",NUM_OF_REAL_CONST++);	
													  fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
													  
													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");
													  
												 }
												 else{ /* -- STACK -- */
													
													  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");			
												}
									 break;
									 case BOOL:
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
								 }
							
							break;
							case REAL:
							
								 switch(rhs->typos){
										 
										 
										 case INT:
										 
												 if(rhs->sclass == REGISTER){
													 
													  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													  fprintf(text,"fild dword [rgs]\n");
													  
													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");
												  
												 }
												 else if(rhs->sclass == CONSTANT)
												 {
													 
													 switch (p->pAstNode[1]->NodeType){
														 
															case astLeOp:
																sn->timi = (lhs->dtimi <= rhs->timi);
																
															break;
															case astLOp:
																sn->timi  = (lhs->dtimi < rhs->timi);					
															break;
															case astGOp:
																sn->timi  = (lhs->dtimi > rhs->timi);					
															break;
															case astGeOp:
																sn->timi = (lhs->dtimi >= rhs->timi);					
															break;
															case astEOp:
																sn->timi = (lhs->dtimi == rhs->timi);					
															break;
															case astNeOp:
																sn->timi = (lhs->dtimi != rhs->timi);					
															break;
														}
													
													sn->sclass = CONSTANT; 
												 }
												 else if(rhs->sclass == MEMORY){
													  
													  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													  fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
													  
													  fprintf(text,"fcomip\n");
													  fprintf(text,"ffreep\n");
													  
												 }
												 else{ /* -- STACK -- */
													
													  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");			
												}
										 break;
										 case REAL:
										 
													 if(rhs->sclass == REGISTER){
														 
														  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
														  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
														  fprintf(text,"fld qword [frgs]\n");
														  
														  fprintf(text,"fcomip\n");
														  fprintf(text,"ffreep\n");
														  
													 }
													 else if(rhs->sclass == CONSTANT)
													 {
														 
														 switch (p->pAstNode[1]->NodeType){
															 
																case astLeOp:
																
																	sn->timi = (lhs->dtimi <= rhs->dtimi);
																	
																break;
																case astLOp:
																
																	sn->timi  = (lhs->dtimi < rhs->dtimi);		
																	
																break;
																case astGOp:
																
																	sn->timi  = (lhs->dtimi > rhs->dtimi);	
																	
																break;
																case astGeOp:
																
																	sn->timi = (lhs->dtimi >= rhs->dtimi);		
																	
																break;
																case astEOp:
																
																	sn->timi = (lhs->dtimi == rhs->dtimi);		
																	
																break;
																case astNeOp:
																
																	sn->timi = (lhs->dtimi != rhs->dtimi);	
																	
																break;
															}
														
														sn->sclass = CONSTANT; 
													 }
													 else if(rhs->sclass == MEMORY){
														  
														  fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
														  fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
														  fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
														  
														  fprintf(text,"fcomip\n");
														  fprintf(text,"ffreep\n");
														  
													 }
													 else{ /* -- STACK -- */
														
														  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");			
													}
										 break;
										 case BOOL:
											printf("Error: bad operand types for binary operator \n");
											exit(1);
										 break;
									 }
								
								break;
								case BOOL:
							
								 switch(rhs->typos){
									 
									 
									 case BOOL:
									 
											//same check
									 
											 if(rhs->sclass == REGISTER){
					 
												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[rgs]\n");
											  
											 }
											 else if(rhs->sclass == CONSTANT)
											 {
												 
												 switch (p->pAstNode[1]->NodeType){
													 
														case astLeOp:
															sn->timi = (lhs->timi <= rhs->timi);
															
														break;
														case astLOp:
															sn->timi  = (lhs->timi < rhs->timi);					
														break;
														case astGOp:
															sn->timi  = (lhs->timi > rhs->timi);					
														break;
														case astGeOp:
															sn->timi = (lhs->timi >= rhs->timi);					
														break;
														case astEOp:
															sn->timi = (lhs->timi == rhs->timi);					
														break;
														case astNeOp:
															sn->timi = (lhs->timi != rhs->timi);					
														break;
													}
												
												sn->sclass = CONSTANT; 
											 }
											 else if(rhs->sclass == MEMORY){
												  
												  fprintf(text,"mov eax,%d\n",lhs->timi);
												  fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
												  
											 }
											 else{ /* -- STACK -- */
												
												  fprintf(text,"ERROR COMPEXPR[CONSTANT-STACK]\n");			
											}
									 break;
									 case REAL:
									 
										    printf("Error: bad operand types for binary operator \n");
											exit(1);  
											
									 break;
									 case INT:
									 
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
								 }
							
							break;
						  
							}
							
	  
			
      break;
      case STACK:
	  
				switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
									 
												// -- POP -- //
												fprintf(text,"pop eax\n");
												
													   
												if(rhs->sclass == MEMORY){
														   
													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
													
												 }
												else if (rhs->sclass == REGISTER) {
															  
													fprintf(text,"cmp eax,[rgs]\n");
															  
												 }
												else if(rhs->sclass == CONSTANT)  {
															   
													fprintf(text,"cmp eax,%d\n",rhs->timi);
													
												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");				
												 }
									 
									 break;
									 case REAL:
									 
												// -- POP -- //
												fprintf(text,"fild dword [esp]\n");
												fprintf(text,"add esp,4\n");
												
													   
												if(rhs->sclass == MEMORY){
														   
													 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
													 
													 fprintf(text,"fcomip\n");
													 fprintf(text,"ffreep\n");
													
												 }
												else if (rhs->sclass == REGISTER) {
															  
													 fprintf(text,"fld qword [frgs]\n");
													 
													 fprintf(text,"fcomip\n");
													 fprintf(text,"ffreep\n");
															  
												 }
												else if(rhs->sclass == CONSTANT)  {
															   
													fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
												    fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
												 
													fprintf(text,"fcomip\n");
													fprintf(text,"ffreep\n");
													
												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");				
												 }
									 break;
									 case BOOL:
									 
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
									 
								 }
							
							break;
							case REAL:
							
									 switch(rhs->typos){
									 
											 case INT:
											 
														// -- POP -- //
														fprintf(text,"fld qword [esp]\n");
														fprintf(text,"add esp,8\n");
														
															   
														 if(rhs->sclass == MEMORY){
														   
															 fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
															 
															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");
															
														 }
														else if (rhs->sclass == REGISTER) {
																	  
															 fprintf(text,"fild dword [rgs]\n");
															 
															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");
																	  
														 }
														else if(rhs->sclass == CONSTANT)  {
																	   
															fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->dtimi);
															fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);	
														 
															fprintf(text,"fcomip\n");
															fprintf(text,"ffreep\n");
															
														 }
														else { /* -- STACK -- */
														   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");				
														 }
											 
											 break;
											 case REAL:
											 
														// -- POP -- //
														fprintf(text,"fld qword [esp]\n");
														fprintf(text,"add esp,8\n");
														
															   
														if(rhs->sclass == MEMORY){
																   
															 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
															 
															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");
															
														 }
														else if (rhs->sclass == REGISTER) {
																	  
															 fprintf(text,"fld qword [frgs]\n");
															 
															 fprintf(text,"fcomip\n");
															 fprintf(text,"ffreep\n");
																	  
														 }
														else if(rhs->sclass == CONSTANT)  {
																	   
															fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
														 
															fprintf(text,"fcomip\n");
															fprintf(text,"ffreep\n");
															
														 }
														else { /* -- STACK -- */
														   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");				
														 }
											 break;
											 case BOOL:
									 
													printf("Error: bad operand types for binary operator \n");
													exit(1);
											 break;
									 
								 }
						break;
						case BOOL:
							
								 switch(rhs->typos){
									 
									 case BOOL:
												// same check
												// -- POP -- //
												fprintf(text,"pop eax\n");
												
													   
												if(rhs->sclass == MEMORY){
														   
													fprintf(text,"cmp eax,[%s]\n",rhs->pseudonym);
													
												 }
												else if (rhs->sclass == REGISTER) {
															  
													fprintf(text,"cmp eax,[rgs]\n");
															  
												 }
												else if(rhs->sclass == CONSTANT)  {
															   
													fprintf(text,"cmp eax,%d\n",rhs->timi);
													
												 }
												else { /* -- STACK -- */
												   fprintf(text,"ERROR COMPEXPR[STACK-STACK]\n");				
												 }
									 
									 break;
									 case REAL:
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
									 case INT:
									 
											printf("Error: bad operand types for binary operator \n");
											exit(1);
									 break;
									 
								 }
							
							break;
						}
							
       		
      break;
   }
  
 
	if(sn->sclass == REGISTER ) 
		 {
			 
			fprintf(text,"mov eax,1\n");
			
			//Set 1 in register A if the entire logical expression is true else set 0 (ENTA 0)
            switch (p->pAstNode[1]->NodeType){
					case astLeOp:
						     
							 if(lhs->typos == REAL || rhs->typos == REAL)
								 fprintf(text,"jae $ + 7\n");
							 else
								 fprintf(text,"jle $ + 7\n");
							 
							 fprintf(text,"mov eax,0\n");
							 
						break;	 
					case astLOp: 
					
					         if(lhs->typos == REAL || rhs->typos == REAL)
								 fprintf(text,"ja $ + 7\n");
							 else
								 fprintf(text,"jl $ + 7\n");
							 
							 fprintf(text,"mov eax,0\n");
							
					break;
					case astGOp:
					
						      if(lhs->typos == REAL || rhs->typos == REAL)
								 fprintf(text,"jb $ + 7\n");
							  else
								 fprintf(text,"jg $ + 7\n");
							 
							 fprintf(text,"mov eax,0\n");
							
					break;
					case astGeOp:
					
							 if(lhs->typos == REAL || rhs->typos == REAL)
								 fprintf(text,"jbe $ + 7\n");
							 else
								 fprintf(text,"jge $ + 7\n");
							 
							 fprintf(text,"mov eax,0\n");
							
					break;
					case astEOp:
					         
							 
							 fprintf(text,"je $ + 7\n");
							 fprintf(text,"mov eax,0\n");
							
					break;
					case astNeOp:
					         fprintf(text,"jne $ + 7\n");
							 fprintf(text,"mov eax,0\n");
					break;
			}
			
			if (leftChild == 1){
				
				         // -- PUSH -- //
						 fprintf(text,"push eax\n");
						 sn->sclass=STACK;
			}else {
				
				fprintf(text,"mov [rgs],eax\n");
				
			}
	}
			   
	push_vs(sn);
}   


//Add Expression
void ProcessAddExpr(AstNode *p, int lev, int lvalue, int leftChild){

   symbol *lhs, *rhs, *sn;
   
   //Code Generation for left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();
   
   //Code Generation for right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();
   
   sn=new_symbol("");
   sn->lvalue =0;
   sn->sclass=REGISTER;
   
   if(p->pAstNode[1]->NodeType == astAddOp) {
	   
  
	    switch(lhs->sclass) 
		   {
			  case MEMORY:
			  
					switch(lhs->typos){
						
						case INT:
									
								switch(rhs->typos){
									
									case INT:
											 
											 sn->typos=INT;
											 
											 if(rhs->sclass == REGISTER) 
											 {
												 
													fprintf(text,"mov eax,[rgs]\n");
													fprintf(text,"add [%s]\n", lhs->pseudonym);
													//fprintf(text,"STA AX\n");
												
											 }
											 else if(rhs->sclass == CONSTANT)    
											 {
												
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"add eax,%d\n", rhs->timi);
													//fprintf(text,"STA AX\n");
													
												
											 }else if(rhs->sclass == MEMORY){ 
												 
												 
												 fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												 fprintf(text,"add eax,[%s]\n",rhs->pseudonym);
												// fprintf(text,"STA AX\n");
												 
												
											 }
											 else if(rhs->sclass = STACK){
												 
												 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
												 
											 }
									break;
									
									case REAL:
													sn->typos=REAL;
									
											         if(rhs->sclass == REGISTER){
														 
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fadd qword [frgs]\n");
															//fprintf(text,"fldcw [cw]\n");
														
													 }
													 else if(rhs->sclass == CONSTANT)    
													 {
														
															fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
															
													 }else if(rhs->sclass == MEMORY){ 
														 
														 
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fadd qword [%s]\n", rhs->pseudonym);
															//fprintf(text,"fldcw [cw]\n");
														 
														
													 }
													 else if(rhs->sclass = STACK){
														 
														 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
														 
												  }
									break;
								}
					    break;
						case REAL:
									
								switch(rhs->typos){
											
											case INT:
													 sn->typos=REAL;
					  
													 if(rhs->sclass == REGISTER){
														 
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fiadd dword [rgs]\n");
															
													 }
													 else if(rhs->sclass == CONSTANT)    
													 {
															fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);	
															fprintf(text,"fiadd dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
														
													 }else if(rhs->sclass == MEMORY){ 
														 
														 
														 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
														 fprintf(text,"fiadd dword [%s]\n",rhs->pseudonym);
														
														 
														
													 }
													 else if(rhs->sclass = STACK){
														 
														 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
														 
													 }
											break;
											
											case REAL:
											
															sn->typos=REAL;
											
													         if(rhs->sclass == REGISTER) {
																 
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fadd qword [frgs]\n");
																
															 }
															 else if(rhs->sclass == CONSTANT)    
															 {
																
																	fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
																		
																
															 }else if(rhs->sclass == MEMORY){ 
																 
																 
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
																 
																
															 }
															 else if(rhs->sclass = STACK){
																 
																 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
																 
														  }
											break;
										}
						break;
					}
			  break;
			  
			  case STACK:
			  
						switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
												sn->typos=INT;
												 // -- POP -- //
												 fprintf(text,"pop eax\n");
													
													
											   
											     if(rhs->sclass == MEMORY) {
												   
												     fprintf(text,"add eax,[%s]\n",rhs->pseudonym);
												     // fprintf(text,"STA AX\n");
												   
												   
												 }
											     else if (rhs->sclass == REGISTER) {
													  
													 fprintf(text,"add eax,[rgs]\n");
													 //fprintf(text,"STA AX\n");
													  
												 }
												 else if(rhs->sclass == CONSTANT)  {
													   
													 fprintf(text,"add eax,%d\n",rhs->timi);
													 // fprintf(text,"STA AX\n");
												 }
									 
									 break;
									 case REAL:
												sn->typos=REAL;
									             // -- POP -- //
												 fprintf(text,"fild dword [esp]\n");
												 fprintf(text,"add esp,4\n");
													
											   
											     if(rhs->sclass == MEMORY) {
												   
												     fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
												     // fprintf(text,"STA AX\n");
												   
												   
												 }
											     else if (rhs->sclass == REGISTER) {
													  
													 fprintf(text,"fadd qword [frgs]\n");
													 //fprintf(text,"STA AX\n");
													  
												 }
												 else if(rhs->sclass == CONSTANT)  {
													   
													 	fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
														fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
													 // fprintf(text,"STA AX\n");
												 }
									 
									 
									 
									 break;
									 
								 }
							
							break;
							case REAL:
									
									 // -- POP -- //
									 fprintf(text,"fld qword [esp]\n");
									 fprintf(text,"add esp,8\n");	
							
									 switch(rhs->typos){
											 
											 case INT:
														 sn->typos=REAL;
														
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fiadd dword [%s]\n",rhs->pseudonym);
															 // fprintf(text,"STA AX\n");
														   
														   
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fiadd dword [rgs]\n");
															 //fprintf(text,"STA AX\n");
															  
														 }
														 else if(rhs->sclass == CONSTANT)  {
															   
															 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
														     fprintf(text,"fiadd dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
											 
											 break;
											 case REAL:
											 
														 sn->typos=REAL;
														 
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
															 // fprintf(text,"STA AX\n");
														   
														   
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fadd qword [frgs]\n");
															 //fprintf(text,"STA AX\n");
															  
														 }
														 else if(rhs->sclass == CONSTANT)  {
															   
																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fadd qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
											 
											 
											 
											 break;
											 
										 }
							
							break;
					  
						}
						
			 
				
			  break;
			  case CONSTANT:
			  
					switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
												sn->typos= INT;
												
												if(rhs->sclass == MEMORY){
													
													fprintf(text,"mov eax,%d\n",lhs->timi);
													fprintf(text,"add eax,[%s]\n",rhs->pseudonym);  
													//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													sn->timi = lhs->timi + rhs->timi;
													sn->sclass=CONSTANT;
													
												 }
												 else if(rhs->sclass == REGISTER){
													 
														fprintf(text,"mov eax,%d\n",lhs->timi);
														fprintf(text,"add eax,[rgs]\n");
														//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == STACK){
													 
													 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
													 
												 }
																 
									 
									 break;
									 case REAL:
												 sn->typos=REAL;
												
												 if(rhs->sclass == MEMORY){
													 
													 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													 fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													
													 fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);  
													//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													sn->dtimi = lhs->timi + rhs->dtimi;
													sn->sclass=CONSTANT;
													
												 }
												 else if(rhs->sclass == REGISTER){
													 
														 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													     fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													 
														 fprintf(text,"fadd qword [frgs]\n"); 
														//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == STACK){
													 
													 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
													 
												 }
									 
									 break;
									 
								 }
							
							break;
							case REAL:
							
									  switch(rhs->typos){
											 
											 case INT:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fiadd dword [%s]\n",rhs->pseudonym);
															//fprintf(text,"STA AX\n");
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															sn->dtimi = lhs->dtimi + rhs->timi;
															sn->sclass=CONSTANT;
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fiadd dword [rgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																		 
											 
											 break;
											 case REAL:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fadd qword [%s]\n",rhs->pseudonym);
															//fprintf(text,"STA AX\n");
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															sn->dtimi = lhs->dtimi + rhs->dtimi;
															sn->sclass=CONSTANT;
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fadd qword [frgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																
											 
											 break;
											 
										 }
							
							break;
					  
						}
						
			  break;
			  case REGISTER:
			       fprintf(text,"ERROR ADDEXPR[REGISTER-]\n");
			  break;
			 
		   }
		   
		 
			  
   
   
   }
   
   
   else if(p->pAstNode[1]->NodeType == astSubOp)
   {
			switch(lhs->sclass) 
		   {
			  case MEMORY:
			  
					switch(lhs->typos){
						
						case INT:
									
								switch(rhs->typos){
									
									case INT:
											 
											 sn->typos=INT;
											 
											 if(rhs->sclass == REGISTER) 
											 {
												 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"sub eax,[rgs]\n");
													//fprintf(text,"STA AX\n");
												
											 }
											 else if(rhs->sclass == CONSTANT)    
											 {
												
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"sub eax,%d\n", rhs->timi);
													//fprintf(text,"STA AX\n");
													
												
											 }else if(rhs->sclass == MEMORY){ 
												 
												 
												 fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
												 fprintf(text,"sub eax,[%s]\n",rhs->pseudonym);
												// fprintf(text,"STA AX\n");
												 
												
											 }
											 else if(rhs->sclass = STACK){
												 
												 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
												 
											 }
									break;
									
									case REAL:
													sn->typos=REAL;
									
											         if(rhs->sclass == REGISTER){
														 
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fsub qword [frgs]\n");
															//fprintf(text,"fldcw [cw]\n");
														
													 }
													 else if(rhs->sclass == CONSTANT)    
													 {
														
															fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);	
															
													 }else if(rhs->sclass == MEMORY){ 
														 
														 
															fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
															fprintf(text,"fsub qword [%s]\n", rhs->pseudonym);
															//fprintf(text,"fldcw [cw]\n");
														 
														
													 }
													 else if(rhs->sclass = STACK){
														 
														 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
														 
												  }
									break;
								}
					    break;
						case REAL:
									
								switch(rhs->typos){
											
											case INT:
													 sn->typos=REAL;
					  
													 if(rhs->sclass == REGISTER){
														 
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fisub dword [rgs]\n");
															
													 }
													 else if(rhs->sclass == CONSTANT)    
													 {
															fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);	
															fprintf(text,"fisub dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
														
													 }else if(rhs->sclass == MEMORY){ 
														 
														 
														 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
														 fprintf(text,"fisub dword [%s]\n",rhs->pseudonym);
														
														 
														
													 }
													 else if(rhs->sclass = STACK){
														 
														 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
														 
													 }
											break;
											
											case REAL:
											
															sn->typos=REAL;
											
													         if(rhs->sclass == REGISTER) {
																 
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fsub qword [frgs]\n");
																
															 }
															 else if(rhs->sclass == CONSTANT)    
															 {
																
																	fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
																		
																
															 }else if(rhs->sclass == MEMORY){ 
																 
																 
																	fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																	fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
																 
																
															 }
															 else if(rhs->sclass = STACK){
																 
																 fprintf(text,"ERROR ADDEXPR[MEMORY-STACK]\n");
																 
														  }
											break;
										}
						break;
					}
			  break;
			  
			  case STACK:
			  
						switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
												sn->typos=INT;
												 // -- POP -- //
												 fprintf(text,"pop eax\n");
													
													
											   
											     if(rhs->sclass == MEMORY) {
												   
												     fprintf(text,"sub eax,[%s]\n",rhs->pseudonym);
												     // fprintf(text,"STA AX\n");
												   
												   
												 }
											     else if (rhs->sclass == REGISTER) {
													  
													 fprintf(text,"sub eax,[rgs]\n");
													 //fprintf(text,"STA AX\n");
													  
												 }
												 else if(rhs->sclass == CONSTANT)  {
													   
													 fprintf(text,"sub eax,%d\n",rhs->timi);
													 // fprintf(text,"STA AX\n");
												 }
									 
									 break;
									 case REAL:
												sn->typos=REAL;
									             // -- POP -- //
												 fprintf(text,"fild dword [esp]\n");
												 fprintf(text,"add esp,4\n");
													
											   
											     if(rhs->sclass == MEMORY) {
												   
												     fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
												     // fprintf(text,"STA AX\n");
												   
												   
												 }
											     else if (rhs->sclass == REGISTER) {
													  
													 fprintf(text,"fsub qword [frgs]\n");
													 //fprintf(text,"STA AX\n");
													  
												 }
												 else if(rhs->sclass == CONSTANT)  {
													   
													 	fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
														fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
													 // fprintf(text,"STA AX\n");
												 }
									 
									 
									 
									 break;
									 
								 }
							
							break;
							case REAL:
									
									 // -- POP -- //
									 fprintf(text,"fld qword [esp]\n");
									 fprintf(text,"add esp,8\n");	
							
									 switch(rhs->typos){
											 
											 case INT:
														 sn->typos=REAL;
														
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fisub dword [%s]\n",rhs->pseudonym);
															 // fprintf(text,"STA AX\n");
														   
														   
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fisub dword [rgs]\n");
															 //fprintf(text,"STA AX\n");
															  
														 }
														 else if(rhs->sclass == CONSTANT)  {
															   
															 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
														     fprintf(text,"fisub dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
											 
											 break;
											 case REAL:
											 
														 sn->typos=REAL;
														 
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
															 // fprintf(text,"STA AX\n");
														   
														   
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fsub qword [frgs]\n");
															 //fprintf(text,"STA AX\n");
															  
														 }
														 else if(rhs->sclass == CONSTANT)  {
															   
																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fsub qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
											 
											 
											 
											 break;
											 
										 }
							
							break;
					  
						}
						
			 
				
			  break;
			  case CONSTANT:
			  
					switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
												sn->typos= INT;
												
												if(rhs->sclass == MEMORY){
													
													fprintf(text,"mov eax,%d\n",lhs->timi);
													fprintf(text,"sub eax,[%s]\n",rhs->pseudonym);  
													//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													sn->timi = lhs->timi - rhs->timi;
													sn->sclass=CONSTANT;
													
												 }
												 else if(rhs->sclass == REGISTER){
													 
														fprintf(text,"mov eax,%d\n",lhs->timi);
														fprintf(text,"sub eax,[rgs]\n");
														//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == STACK){
													 
													 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
													 
												 }
																 
									 
									 break;
									 case REAL:
												 sn->typos=REAL;
												
												 if(rhs->sclass == MEMORY){
													 
													 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													 fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													
													 fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);  
													//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													 
													sn->dtimi = lhs->timi - rhs->dtimi;
													sn->sclass=CONSTANT;
													
												 }
												 else if(rhs->sclass == REGISTER){
													 
														 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													     fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													 
														 fprintf(text,"fsub qword [frgs]\n"); 
														//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == STACK){
													 
													 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
													 
												 }
									 
									 break;
									 
								 }
							
							break;
							case REAL:
							
									  switch(rhs->typos){
											 
											 case INT:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fisub dword [%s]\n",rhs->pseudonym);
															//fprintf(text,"STA AX\n");
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															sn->dtimi = lhs->dtimi - rhs->timi;
															sn->sclass=CONSTANT;
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fisub dword [rgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																		 
											 
											 break;
											 case REAL:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fsub qword [%s]\n",rhs->pseudonym);
															//fprintf(text,"STA AX\n");
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															sn->dtimi = lhs->dtimi - rhs->dtimi;
															sn->sclass=CONSTANT;
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fsub qword [frgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																
											 
											 break;
											 
										 }
							
							break;
					  
						}
						
			  break;
			  case REGISTER:
			       fprintf(text,"ERROR ADDEXPR[REGISTER-]\n");
			  break;
			 
		   }
		   
		   
		   
   }
   
   
   if( (sn->sclass) == REGISTER ){
	   
             if(leftChild == 1){
				  
					// -- PUSH -- //
					switch(sn->typos){
						
						case INT:
							fprintf(text,"push eax\n");
						break;
						case REAL:
							fprintf(text,"sub esp,8\n");
							fprintf(text,"fstp qword [esp]\n");
						break;
					}
					
					sn->sclass=STACK;
						
			}
			else{
				
				switch(sn->typos){
						
						case INT:
							fprintf(text,"mov [rgs],eax\n");
						break;
						case REAL:
							fprintf(text,"fstp qword [frgs]\n");
						break;
					}
						  
				
			 }
	}
			   
   push_vs(sn);
   
}

//True 
void ProcessTrue(AstNode* p){
	push_vs(p->SymbolNode);
	
}

//False
void ProcessFalse(AstNode* p){
	push_vs(p->SymbolNode);
	
}


//Method Call
void ProcessMethodCall(AstNode *p, int lev, int lvalue, int leftChild){
	
	symbol *sn;
	sn = new_symbol("");
	sn->sclass= REGISTER;
	
	sn->typos = p->SymbolNode->typos;
	
	//Code Generation for actual parameters
	CodeGeneration(p->pAstNode[1],lev+1,0,0);	
	
	
	
	//Jump to method
	fprintf(text,"call _%s\n",p->SymbolNode->name);
    
	
	
	
	if(leftChild == 1 ) {
		
			 switch(p->SymbolNode->typos){
						
					case INT:
						fprintf(text,"fistp dword [esp] \n");
					break;
					case REAL:
						fprintf(text,"sub esp,8\n");
						fprintf(text,"fstp qword [esp] \n");
					break;
					case BOOL:
						fprintf(text,"fistp dword [esp] \n");
					break;
					
									 
				}		
		
		
		sn->sclass=STACK;
		
	}
    else{
		
		 switch(p->SymbolNode->typos){
						
					case INT:
						//Store the return value to register RGS
						fprintf(text,"fistp dword [rgs]\n"); 
					break;
					case REAL:
						fprintf(text,"fstp qword [frgs] \n");
					break;
					case BOOL:
						//Store the return value to register RGS
						fprintf(text,"fistp dword [rgs]\n"); 
					break;
									 
				}
		
		
	}
	    
			  
			  
	 push_vs(sn);
		 		 
	
}

//Break Statement
void ProcessBreakStmt(){
	
	fprintf(text,"jmp @ENDWHILE_%d\n",see_wh()->timi);
}

//Mul Expression
void ProcessMulExpr(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

	//Code Generation for the left operand
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,1);
   lhs=pop_vs();
   
   //Code Generation for the right operand
   CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
   rhs=pop_vs();
   
   sn = new_symbol("");
   sn->lvalue = 0;
   sn->sclass = REGISTER;
   
   
  if(p->pAstNode[1]->NodeType == astMulOp){
	  
	   switch(lhs->sclass) 
	   {
			  case MEMORY:
			  
					switch(lhs->typos){
							
							case INT:
							
									 switch(rhs->typos){
										 
										 
										 case INT:
											
											sn->typos = INT;
											if(rhs->sclass == MEMORY) {
												
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
													fprintf(text,"imul eax,[%s]\n",rhs->pseudonym);
													//fprintf(text,"JANZ TOOLARGE\n");
													//fprintf(text,"STX AX\n");
												 }
												 else if(rhs->sclass == CONSTANT) 
												 {
													 
													fprintf(text,"mov eax,[%s]\n",lhs->pseudonym); 
													fprintf(text,"imul eax,%d\n",rhs->timi);
													//fprintf(text,"JANZ TOOLARGE\n");
													//fprintf(text,"STX AX\n");
												   
												 }
												 else if(rhs->sclass == REGISTER)   
												 {
													fprintf(text,"mov eax,[rgs]\n");
													fprintf(text,"imul eax,[%s]\n",lhs->pseudonym);
													//fprintf(text,"JANZ TOOLARGE\n");
													//fprintf(text,"STX %s\n",rhs->name);
													
												 }
												 else{/* --- STACK --- */
													  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
												 }
										 
										 break;
										 case REAL:
												 sn->typos = REAL;
												 if(rhs->sclass == MEMORY) {
												
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
													//fprintf(text,"JANZ TOOLARGE\n");
													//fprintf(text,"STX AX\n");
												 }
												 else if(rhs->sclass == CONSTANT) 
												 {
													 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
													 fprintf(text,"fild dword [%s]\n",lhs->pseudonym); 
													 fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
												   
												 }
												 else if(rhs->sclass == REGISTER)   
												 {
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fmul qword [frgs]\n");
													
												 }
												 else{/* --- STACK --- */
													  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
												 }
										 
										 
										 
										 break;
										 
									 }
							
							break;
							case REAL:
							
										switch(rhs->typos){
												 
												 
												 case INT:
												 
													sn->typos = REAL;
													if(rhs->sclass == MEMORY) {
														
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fimul dword [%s]\n",rhs->pseudonym);
															
														 }
														 else if(rhs->sclass == CONSTANT) 
														 {
															 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															 fprintf(text,"fld qword [%s]\n",lhs->pseudonym); 
															 fprintf(text,"fimul dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
														 }
														 else if(rhs->sclass == REGISTER)   
														 {
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fimul dword [rgs]\n");
															
														 }
														 else{/* --- STACK --- */
															  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
														 }
												 
												 break;
												 case REAL:
												 
														 sn->typos = REAL;
														 
														 if(rhs->sclass == MEMORY) {
														
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
															
														 }
														 else if(rhs->sclass == CONSTANT) 
														 {
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															 fprintf(text,"fld qword [%s]\n",lhs->pseudonym); 
															 fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
														 }
														 else if(rhs->sclass == REGISTER)   
														 {
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fmul qword [frgs]\n");
															
														 }
														 else{/* --- STACK --- */
															  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
														 }
												 
												 
												 
												 break;
												 
											 }
							
									
							break;
					  
						}
					 
			  break;
			case CONSTANT:
			
					        switch(lhs->typos){
									
									case INT:
											 switch(rhs->typos){
												 
												 
												 case INT:
																sn->typos = INT;
																 
																if(rhs->sclass == CONSTANT) 
																 {
																	sn->timi = lhs->timi * rhs->timi;
																	sn->sclass=CONSTANT;
																 }
																 else if (rhs->sclass == MEMORY)     
																 {
																	fprintf(text,"mov eax,%d\n",lhs->timi); 
																	fprintf(text,"imul eax,[%s]\n",rhs->pseudonym);
																	
																 }
																 else if (rhs->sclass == REGISTER) 
																 {
																	fprintf(text,"mov eax,%d\n",lhs->timi); 
																	fprintf(text,"imul eax,[rgs]\n");
																	
																 }
																 else{ /* --- STACK --- */
																	  fprintf(text,"ERROR MULEXPR[CONSTANT-STACK]\n");
																 }
												 break;
												 case REAL:
																sn->typos = REAL;
																if(rhs->sclass == CONSTANT) 
																 {
																	sn->dtimi = lhs->timi * rhs->dtimi;
																	sn->sclass=CONSTANT;
																 }
																 else if (rhs->sclass == MEMORY)     
																 {
																	 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
																     fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++); 
																	 fprintf(text,"fmul qword [%s]\n",rhs->pseudonym); 
																	
																 }
																 else if (rhs->sclass == REGISTER) 
																 {
																	 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
																     fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++); 
																	 fprintf(text,"fmul qword [frgs]\n"); 
																	 
																 }
																 else{ /* --- STACK --- */
																	  fprintf(text,"ERROR MULEXPR[CONSTANT-STACK]\n");
																 }
												 break;
												 
											 }
									
									break;
									case REAL:
									
											  switch(rhs->typos){
														 
														 
														 case INT:
																		sn->typos = REAL;
																		 
																		if(rhs->sclass == CONSTANT) 
																		 {
																			sn->dtimi = lhs->dtimi * rhs->timi;
																			sn->sclass=CONSTANT;
																		 }
																		 else if (rhs->sclass == MEMORY)     
																		 {
																			fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
																			fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++); 
																			
																			fprintf(text,"fimul dword [%s]\n",rhs->pseudonym); 
																			
																		 }
																		 else if (rhs->sclass == REGISTER) 
																		 {
																			fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
																			fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++); 
																			
																			fprintf(text,"fimul dword [rgs]\n"); 
																			
																		 }
																		 else{ /* --- STACK --- */
																			  fprintf(text,"ERROR MULEXPR[CONSTANT-STACK]\n");
																		 }
														 break;
														 case REAL:
																		sn->typos = REAL;
																		if(rhs->sclass == CONSTANT) 
																		 {
																			sn->dtimi = lhs->dtimi * rhs->dtimi;
																			sn->sclass=CONSTANT;
																		 }
																		 else if (rhs->sclass == MEMORY)     
																		 {
																			fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
																			fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++); 
																			
																		    fprintf(text,"fmul qword [%s]\n",rhs->pseudonym); 
																			
																		 }
																		 else if (rhs->sclass == REGISTER) 
																		 {
																			 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
																			 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
																			 
																			 fprintf(text,"fmul qword [frgs]\n"); 
																			 
																		 }
																		 else{ /* --- STACK --- */
																			  fprintf(text,"ERROR MULEXPR[CONSTANT-STACK]\n");
																		 }
														 break;
														 
													 }
									
									break;
							  
								}
			
			  break;
			case STACK:
			
						switch(lhs->typos){
										
										case INT:
										
											 switch(rhs->typos){
												 
												 
												 case INT:
												            sn->typos=INT;
															// -- POP -- //
															fprintf(text,"pop eax\n");
															
																   
															if(rhs->sclass == MEMORY) {
																	   
																fprintf(text,"imul eax,[%s]\n",rhs->pseudonym);
																//fprintf(text,"STX %s\n",sn->name);
															 }
															else if (rhs->sclass == REGISTER) {
																		  
																fprintf(text,"imul eax,[rgs]\n");
																//fprintf(text,"STX %s\n",sn->name);
																		  
															 }
															else if(rhs->sclass == CONSTANT)  {
																		   
																fprintf(text,"imul eax,%d\n",rhs->timi);
																//fprintf(text,"STX %s\n",sn->name);
														}
												 break;
												 case REAL:
												 
														 sn->typos=REAL;
														 // -- POP -- //
														 fprintf(text,"fild dword [esp]\n");
														 fprintf(text,"add esp,4\n");
															
													   
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
															
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fmul qword [frgs]\n");
															
														 }
														 else if(rhs->sclass == CONSTANT)  {
															   
																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
												 
												 break;
												 
											 }
										
										break;
										case REAL:
									
												 // -- POP -- //
												 fprintf(text,"fld qword [esp]\n");
												 fprintf(text,"add esp,8\n");	
										
												 switch(rhs->typos){
														 
														 case INT:
																	 sn->typos=REAL;
																	
																	 if(rhs->sclass == MEMORY) {
																	   
																		 fprintf(text,"fimul dword [%s]\n",rhs->pseudonym);
																		 // fprintf(text,"STA AX\n");
																	   
																	   
																	 }
																	 else if (rhs->sclass == REGISTER) {
																		  
																		 fprintf(text,"fimul dword [rgs]\n");
																		 //fprintf(text,"STA AX\n");
																		  
																	 }
																	 else if(rhs->sclass == CONSTANT)  {
																		   
																		 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
																		 fprintf(text,"fimul dword [INT_%d]\n",NUM_OF_INT_CONST++);
																		
																		 // fprintf(text,"STA AX\n");
																	 }
														 
														 break;
														 case REAL:
														 
																	 sn->typos=REAL;
																	 
																	 if(rhs->sclass == MEMORY) {
																	   
																		 fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
																		 // fprintf(text,"STA AX\n");
																	   
																	   
																	 }
																	 else if (rhs->sclass == REGISTER) {
																		  
																		 fprintf(text,"fmul qword [frgs]\n");
																		 //fprintf(text,"STA AX\n");
																		  
																	 }
																	 else if(rhs->sclass == CONSTANT)  {
																		   
																			fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																			fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
																		
																		 // fprintf(text,"STA AX\n");
																	 }
														 
														 
														 
														 break;
														 
													 }
							
									 break;
								  
									}
							
				 
						
				
			  break;
			  case REGISTER:
						fprintf(text,"ERROR MULEXPR[REGISTER-]\n");
			  break;
	   }
  }
   else if (p->pAstNode[1]->NodeType == astDivOp || p->pAstNode[1]->NodeType == astModOp) {
	   
	  switch(lhs->sclass) 
		   {
			
			case MEMORY:
				
				switch(lhs->typos){
							
							case INT:
							
									 switch(rhs->typos){
										 
										 
										 case INT:
											
											sn->typos = INT;
											if(rhs->sclass == MEMORY){
												
														
														fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
														fprintf(text,"cdq\n");
														fprintf(text,"mov ebx,[%s]\n",rhs->pseudonym);
														fprintf(text,"idiv ebx\n");
														
													 }
													 else if(rhs->sclass == CONSTANT) 
													 {
														//Checks if the divisor equals zero
														if(rhs->timi == 0) {
															
															printf("Error: You can't divide by zero\n");
															exit(1);
														}
														
														fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
														fprintf(text,"cdq\n");
														fprintf(text,"mov ebx,%d\n",rhs->timi);
														fprintf(text,"idiv ebx\n");
														
													   
													 }
													 else if (rhs->sclass == REGISTER)   
													 {
														 
														 
														fprintf(text,"mov eax,[%s]\n",lhs->pseudonym);
														fprintf(text,"cdq\n");
														fprintf(text,"mov ebx,[rgs]\n");
														fprintf(text,"idiv ebx\n");
													
														
													 }
													 else { /* -- STACK -- */
														fprintf(text,"ERROR DIVEXPR[MEMORY-STACK]\n");
													}
										 
										 break;
										 case REAL:
										 
												 sn->typos = REAL;
												 
												 if(rhs->sclass == MEMORY) {
												
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);
													
												 }
												 else if(rhs->sclass == CONSTANT) 
												 {
													//Checks if the divisor equals zero
													 if(rhs->dtimi == 0) {
															
														printf("Error: You can't divide by zero\n");
														exit(1);
													 }
													 
													 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
													 fprintf(text,"fild dword [%s]\n",lhs->pseudonym); 
													 fprintf(text,"fdiv qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
													
												   
												 }
												 else if(rhs->sclass == REGISTER)   
												 {
													fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
													fprintf(text,"fdiv qword [frgs]\n");
													
												 }
												 else{/* --- STACK --- */
													  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
												 }
										 
										 
										 
										 break;
										 
									 }
							
							break;
							case REAL:
							
										switch(rhs->typos){
												 
												 
												 case INT:
												 
													sn->typos = REAL;
													
													if(rhs->sclass == MEMORY) {
														
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fidiv dword [%s]\n",rhs->pseudonym);
															
														 }
														 else if(rhs->sclass == CONSTANT) 
														 {
															 //Checks if the divisor equals zero
															 if(rhs->timi == 0) {
															
																printf("Error: You can't divide by zero\n");
																exit(1);
															 }
															 
															 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
															 fprintf(text,"fld qword [%s]\n",lhs->pseudonym); 
															 fprintf(text,"fidiv dword [INT_%d]\n",NUM_OF_INT_CONST++);
															
														 }
														 else if(rhs->sclass == REGISTER)   
														 {
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fidiv dword [rgs]\n");
															
														 }
														 else{/* --- STACK --- */
															  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
														 }
												 
												 break;
												 case REAL:
												 
														 sn->typos = REAL;
														 
														 if(rhs->sclass == MEMORY) {
														
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);
															
														 }
														 else if(rhs->sclass == CONSTANT) 
														 {
															 //Checks if the divisor equals zero
															 if(rhs->dtimi == 0) {
															
																printf("Error: You can't divide by zero\n");
																exit(1);
														     }
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
															 fprintf(text,"fld qword [%s]\n",lhs->pseudonym); 
															 fprintf(text,"fdiv qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
														 }
														 else if(rhs->sclass == REGISTER)   
														 {
															fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
															fprintf(text,"fdiv qword [frgs]\n");
															
														 }
														 else{/* --- STACK --- */
															  fprintf(text,"ERROR MULEXPR[MEMORY-STACK]\n");
														 }
												 
												 
												 
												 break;
												 
											 }
							
									
							break;
					  
						}
					
			break;
			case CONSTANT:
			
					switch(lhs->typos){
							
							case INT:
							
								 switch(rhs->typos){
									 
									 case INT:
												
												 sn->typos= INT;
												
												 if(rhs->sclass == CONSTANT) 
												 {
													//Checks if the divisor equals zero
													if(rhs->timi != 0){
														
														if(p->pAstNode[1]->NodeType == astDivOp)
															sn->timi = lhs->timi / rhs->timi;
														else
															sn->timi = lhs->timi % rhs->timi;
														
														sn->sclass=CONSTANT;
														
													}
													else {
														
														printf("Error: You can't divide by zero\n");
														exit(1);
														
													}
													
												 }
												 else if (rhs->sclass == MEMORY)     
												 {
													 
													fprintf(text,"mov eax,%d\n",lhs->timi);
													fprintf(text,"cdq\n");
													fprintf(text,"mov ebx,[%s]\n",rhs->pseudonym);
													fprintf(text,"idiv ebx\n");
													
													
												 }
												 else if (rhs->sclass == REGISTER) 
												 {
													
													fprintf(text,"mov eax,%d\n",lhs->timi); 
													fprintf(text,"cdq\n");
													fprintf(text,"mov ebx,[rgs]\n");
													fprintf(text,"idiv ebx\n");
													
													 
												 } else { /* -- STACK -- */
													fprintf(text,"ERROR DIVEXPR[CONSTANT-STACK]\n");				
													}				 
									 
									 break;
									 case REAL:
												 sn->typos=REAL;
												
												 if(rhs->sclass == MEMORY){
													 
													 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													 fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													
													 fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);  
													//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == CONSTANT){
													
												    if(rhs->dtimi != 0){
														
														if(p->pAstNode[1]->NodeType == astDivOp)
															sn->dtimi = lhs->timi / rhs->dtimi;
														else
															sn->dtimi = fmod(lhs->timi , rhs->dtimi);
														
														sn->sclass=CONSTANT;
														
													}
													else {
														
														printf("Error: You can't divide by zero\n");
														exit(1);
														
													}
													
												
												 }
												 else if(rhs->sclass == REGISTER){
													 
														 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,lhs->timi);
													     fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);
													 
														 fprintf(text,"fdiv qword [frgs]\n"); 
														//fprintf(text,"STA AX\n");
													
												 }
												 else if(rhs->sclass == STACK){
													 
													 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
													 
												 }
									 
									 break;
									 
								 }
							
							break;
							case REAL:
							
									  switch(rhs->typos){
											 
											 case INT:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fidiv dword [%s]\n",rhs->pseudonym);
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															 //Checks if the divisor equals zero
															 if(rhs->timi != 0){
																
																if(p->pAstNode[1]->NodeType == astDivOp)
																	sn->dtimi = lhs->dtimi / rhs->timi;
																else
																	sn->dtimi = fmod(lhs->dtimi , rhs->timi);
																
																sn->sclass=CONSTANT;
																
															 }
															 else {
																
																printf("Error: You can't divide by zero\n");
																exit(1);
																
															}
															 
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fidiv dword [rgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																		 
											 
											 break;
											 case REAL:
														sn->typos= REAL;
														
														if(rhs->sclass == MEMORY){
															
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);
															//fprintf(text,"STA AX\n");
															
														 }
														 else if(rhs->sclass == CONSTANT){
															 
															 if(rhs->dtimi != 0){
														
																 if(p->pAstNode[1]->NodeType == astDivOp)
																		sn->dtimi = lhs->dtimi / rhs->dtimi;
																 else
																		sn->dtimi = fmod(lhs->dtimi , rhs->dtimi);
																
																 sn->sclass=CONSTANT;
																
															}
															else {
																
																printf("Error: You can't divide by zero\n");
																exit(1);
																
															}
															
														 }
														 else if(rhs->sclass == REGISTER){
															 
															 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,lhs->dtimi);
													         fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 fprintf(text,"fdiv qword [frgs]\n");
															
														 }
														 else if(rhs->sclass == STACK){
															 
															 fprintf(text,"ERROR ADDEXPR[CONSTANT-STACK]\n");
															 
														 }
																
											 
											 break;
											 
										 }
							
							break;
					  
						}
					
			break;
			case STACK:
			
				    switch(lhs->typos){
										
										case INT:
										
											 switch(rhs->typos){
												 
												 
												 case INT:
												            sn->typos=INT;
															
															if(rhs->sclass == MEMORY) {
							
																  // -- POP -- //
																 fprintf(text,"pop eax\n");
																 
																 fprintf(text,"cdq\n");
																 fprintf(text,"mov ebx,[%s]\n",rhs->pseudonym);
																 fprintf(text,"idiv ebx\n");
																
															 }
															else if (rhs->sclass == REGISTER) {
																
																 
																 // -- POP -- //	
																 fprintf(text,"pop eax\n");
																 
																 fprintf(text,"cdq\n");
																 fprintf(text,"mov ebx,[rgs]\n");	  
																 fprintf(text,"idiv ebx\n");
																
																		  
															 }
															else if(rhs->sclass == CONSTANT)  {
																
																 if(rhs->timi == 0) {
																
																	printf("Error: You can't divide by zero\n");
																	exit(1);
																 }
																 
																  // -- POP -- //
																 fprintf(text,"pop eax\n");
																 
																 fprintf(text,"cdq\n");
																 fprintf(text,"mov ebx,%d\n",rhs->timi);
																 fprintf(text,"idiv ebx\n");
																
															 } 
															else { /* -- STACK -- */
																fprintf(text,"ERROR DIVEXPR[STACK-STACK]\n");					
															}
												 break;
												 case REAL:
												 
														 sn->typos=REAL;
														 // -- POP -- //
														 fprintf(text,"fild dword [esp]\n");
														 //fprintf(text,"add esp,4\n");
															
													   
														 if(rhs->sclass == MEMORY) {
														   
															 fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);
															
														 }
														 else if (rhs->sclass == REGISTER) {
															  
															 fprintf(text,"fdiv qword [frgs]\n");
															
														 }
														 else if(rhs->sclass == CONSTANT)  {
															 
																 if(rhs->dtimi == 0) {
																
																	printf("Error: You can't divide by zero\n");
																	exit(1);
																 }
															   
																fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																fprintf(text,"fdiv qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
															
															 // fprintf(text,"STA AX\n");
														 }
												 
												 break;
												 
											 }
										
										break;
										case REAL:
									
												 // -- POP -- //
												 fprintf(text,"fld qword [esp]\n");
												 //fprintf(text,"add esp,8\n");	
										
												 switch(rhs->typos){
														 
														 case INT:
																	 sn->typos=REAL;
																	
																	 if(rhs->sclass == MEMORY) {
																	   
																		 fprintf(text,"fidiv dword [%s]\n",rhs->pseudonym);
																		 // fprintf(text,"STA AX\n");
																	   
																	   
																	 }
																	 else if (rhs->sclass == REGISTER) {
																		  
																		 fprintf(text,"fidiv dword [rgs]\n");
																		 //fprintf(text,"STA AX\n");
																		  
																	 }
																	 else if(rhs->sclass == CONSTANT)  {
																		 
																		  if(rhs->timi == 0) {
																
																				printf("Error: You can't divide by zero\n");
																				exit(1);
																			
																			}
																		 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
																		 fprintf(text,"fidiv dword [INT_%d]\n",NUM_OF_INT_CONST++);
																		
																		 // fprintf(text,"STA AX\n");
																	 }
														 
														 break;
														 case REAL:
														 
																	 sn->typos=REAL;
																	 
																	 if(rhs->sclass == MEMORY) {
																	   
																		 fprintf(text,"fdiv qword [%s]\n",rhs->pseudonym);
																		 // fprintf(text,"STA AX\n");
																	   
																	   
																	 }
																	 else if (rhs->sclass == REGISTER) {
																		  
																		 fprintf(text,"fdiv qword [frgs]\n");
																		 //fprintf(text,"STA AX\n");
																		  
																	 }
																	 else if(rhs->sclass == CONSTANT)  {
																		 
																			 if(rhs->dtimi == 0) {
																
																				 printf("Error: You can't divide by zero\n");
																				 exit(1);
																			    }
																		   
																			fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
																			fprintf(text,"fdiv qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
																		
																		 // fprintf(text,"STA AX\n");
																	 }
														 
														 
														 
														 break;
														 
													 }
							
									 break;
								  
									}
							
						
				
		    break;
			case REGISTER:
				fprintf(text,"ERROR DIVEXPR[REGISTER-]\n");
		    break;
		   }
	   
   }

   if( (sn->sclass) == REGISTER ) {
		
		     if(leftChild == 1 ){
				
					// -- PUSH -- //
					switch(sn->typos){
						
						case INT:
						
							if(p->pAstNode[1]->NodeType == astModOp)
								fprintf(text,"push edx\n");	
							else
								fprintf(text,"push eax\n");
							
						break;
						case REAL:
						
							if(p->pAstNode[1]->NodeType == astModOp){
								
									
									switch(rhs->typos){
											
										 case INT:
										 
												fprintf(text,"frndint\n");
												//fprintf(text,"fistp dword [eax]\n");
												
												switch(rhs->sclass){
													
													case MEMORY:
														 fprintf(text,"fimul dword [%s]\n",rhs->pseudonym);
													break;
													case REGISTER:
														 fprintf(text,"fimul dword [rgs]\n");
													break;
													case CONSTANT:
														 
														 fprintf(text,"fimul dword [INT_%d]\n",NUM_OF_INT_CONST-1);
													break;
													
												}
												
												//The left operand must be real because we are in case that the right operand is integer
												switch(lhs->typos){
													
													
													case REAL:
													
															switch(lhs->sclass){
																		
																			case MEMORY:
																				 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																			break;
																			case STACK:
																					// -- POP -- //
																					fprintf(text,"fld qword [esp]\n");
																					fprintf(text,"add esp,8\n");	
																			break;
																			case CONSTANT:
																				 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
																			break;
																		
																	}
															fprintf(text,"fsubr\n");
													break;
													
												}
											
										 break;
										 case REAL:
										 
												fprintf(text,"frndint\n");
												
												switch(rhs->sclass){
													
													case MEMORY:
														 fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
													break;
													case REGISTER:
														 fprintf(text,"fmul qword [frgs]\n");
													break;
													case CONSTANT:
														 fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
													break;
													
												}
												
												switch(lhs->typos){
													
													
														case REAL:
														
																switch(lhs->sclass){
																			
																				case MEMORY:
																					 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																				break;
																				case STACK:
																					// -- POP -- //
																					fprintf(text,"fld qword [esp]\n");
																					fprintf(text,"add esp,8\n");	
																				break;
																				case CONSTANT:
																					 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
																				break;
																			
																		}
																fprintf(text,"fsubr\n");
														break;
														case INT:
														
																switch(lhs->sclass){
																			
																				case MEMORY:
																					 fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
																				break;
																				case STACK:
																					 fprintf(text,"fild dword [esp]\n");
																					 fprintf(text,"add esp,4\n");
																				break;
																				case CONSTANT:
																					 fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST-1);
																				break;
																			
																		}
																fprintf(text,"fsubr\n");
														break;
													
												}
												
										 break;
										
									}
									
									
								fprintf(text,"sub esp,8\n");
								fprintf(text,"fstp qword [esp]\n");		
									
							}
							else {
								
								if(lhs->sclass == STACK){
									
									switch (lhs->typos){
										
										case INT:
											fprintf(text,"add esp,4\n");
										break;
										case REAL:
											fprintf(text,"add esp,8\n"); //Useless because after i will push 8 bytes
										break;
									}
									
								}
								
								fprintf(text,"sub esp,8\n");
							    fprintf(text,"fstp qword [esp]\n");
								
							}
							
					break;
					
					}
					

					sn->sclass=STACK;
						
				  }
				  else{
					  
							  switch(sn->typos){
								
								case INT:
								
									if(p->pAstNode[1]->NodeType == astModOp)
										fprintf(text,"mov [rgs],edx\n");	
									else
										fprintf(text,"mov [rgs],eax\n");
								break;
								case REAL:
								
										if(p->pAstNode[1]->NodeType == astModOp){
								
									
												switch(rhs->typos){
														
													 case INT:
													 
															fprintf(text,"frndint\n");
															//fprintf(text,"fistp dword [eax]\n");
															
															switch(rhs->sclass){
																
																case MEMORY:
																	 fprintf(text,"fimul dword [%s]\n",rhs->pseudonym);
																break;
																case REGISTER:
																	 fprintf(text,"fimul dword [rgs]\n");
																break;
																case CONSTANT:
																	 
																	 fprintf(text,"fimul dword [INT_%d]\n",NUM_OF_INT_CONST-1);
																break;
																
															}
															
															//The left operand must be real because we are in case that the right operand is integer
															switch(lhs->typos){
																
																
																case REAL:
																
																		switch(lhs->sclass){
																					
																						case MEMORY:
																							 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																						break;
																						case STACK:
																								// -- POP -- //
																								fprintf(text,"fld qword [esp]\n");
																								fprintf(text,"add esp,8\n");	
																						break;
																						case CONSTANT:
																							 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
																						break;
																					
																				}
																		fprintf(text,"fsubr\n");
																break;
																
															}
														
													 break;
													 case REAL:
													 
															fprintf(text,"frndint\n");
															
															switch(rhs->sclass){
																
																case MEMORY:
																	 fprintf(text,"fmul qword [%s]\n",rhs->pseudonym);
																break;
																case REGISTER:
																	 fprintf(text,"fmul qword [frgs]\n");
																break;
																case CONSTANT:
																	 fprintf(text,"fmul qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
																break;
																
															}
															
															switch(lhs->typos){
																
																
																	case REAL:
																	
																			switch(lhs->sclass){
																						
																							case MEMORY:
																								 fprintf(text,"fld qword [%s]\n",lhs->pseudonym);
																							break;
																							case STACK:
																								// -- POP -- //
																								fprintf(text,"fld qword [esp]\n");
																								fprintf(text,"add esp,8\n");	
																							break;
																							case CONSTANT:
																								 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST-1);
																							break;
																						
																					}
																			fprintf(text,"fsubr\n");
																	break;
																	case INT:
																	
																			switch(lhs->sclass){
																						
																							case MEMORY:
																								 fprintf(text,"fild dword [%s]\n",lhs->pseudonym);
																							break;
																							case STACK:
																								 fprintf(text,"fild dword [esp]\n");
																								 fprintf(text,"add esp,4\n");
																							break;
																							case CONSTANT:
																								 fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST-1);
																							break;
																						
																					}
																			fprintf(text,"fsubr\n");
																	break;
																
															}
															
													 break;
													
												}
												
												
											
											fprintf(text,"fstp qword [frgs]\n");		
												
										}
										else {
											
											if(lhs->sclass == STACK){
									
												switch (lhs->typos){
													
													case INT:
														fprintf(text,"add esp,4\n");
													break;
													case REAL:
														fprintf(text,"add esp,8\n"); //Useless because after i will push 8 bytes
													break;
												}
												
											}
												
											fprintf(text,"fstp qword [frgs]\n");
											
										}
									
								break;
							 } 
					  
					 
					 
					
					 
					  
					  
				  }
			   }
			   
   push_vs(sn);
   
   
}


//Declarations
void ProcessDeclsSeq(AstNode *p,int lev,int lvalue,int leftChild){
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
}

//Declaration List
void ProcessDeclListSeq(AstNode *p,int lev,int lvalue,int leftChild){
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
}

//Declaration
void ProcessDecl(AstNode *p,int lev,int lvalue,int leftChild){
	
							 

	
	int lhs;
	
	lhs  = p->pAstNode[0] -> NodeType;
	
	switch(lhs){
		
		case astInt:
				//Variable Declaration
				fprintf(text,"push 0\n");
		break;
		case astReal:
			
				fprintf(text,"fldz\n");
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fstp qword [esp]\n");
			
		break;
		case astBool:
				//Variable Declaration
				fprintf(text,"push 0\n");
		break;
		
	}
	
	
	//Code Generation for next variables
	CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
}


//Declaration Assign
void ProcessDeclAssign(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol  *rhs;
	int lhs;
	
	lhs = p->pAstNode[0]->NodeType;
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,lvalue,0);
	rhs = pop_vs();
	
	switch(rhs->sclass){
		
		case CONSTANT:
			
			switch(rhs->typos){
				
				case INT:
				
					switch(lhs){
						
						case astInt:
						
							 fprintf(text,"push %d\n",rhs->timi);
							 
					    break;
						case astReal:
							
							 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
							 fprintf(text,"fld dword [INT_%d]\n",NUM_OF_INT_CONST++);
							 fprintf(text,"sub esp,8\n");
							 fprintf(text,"fstp qword [esp]\n");
							
						break;
						case astBool:
						
						    printf("Error: bad operand types for binary operator \n");
							exit(1);
					
					    break;
						
					}
				
				break;
				case REAL:
				
					switch(lhs){
							
							case astInt:
								
								 fprintf(text,"push %d\n",(int) rhs->dtimi);
								 
							break;
							case astReal:
								
								 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
								 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
								 fprintf(text,"sub esp,8\n");
								 fprintf(text,"fstp qword [esp]\n");
								
							break;
							case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
							break;
							
						}
				
				
				break;
				case BOOL:
				
					switch(lhs){
						
						case astInt:
						
							 printf("Error: bad operand types for binary operator \n");
							 exit(1);
							 
					    break;
						case astReal:
							
							 printf("Error: bad operand types for binary operator \n");
							 exit(1);
							
						break;
						case astBool:
						
						     fprintf(text,"push %d\n",rhs->timi);
					
					    break;
						
					}
				
				break;
		  
			 
			
			}
		break;
		case MEMORY:
		
				switch(rhs->typos){
						
						case INT:
						
							switch(lhs){
								
								case astInt:
								
									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);
									 
								break;
								case astReal:
									
									
									 fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");
									
								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								
							}
						
						break;
						case REAL:
						
							switch(lhs){
									
									case astInt:
										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");
										 
									break;
									case astReal:
										
										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");
										
									break;
									case astBool:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
									
								}
						
						
						break;
						case BOOL:
						
							switch(lhs){
								
								case astInt:
									
									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);
									 
								break;
								case astReal:
									
									printf("Error: bad operand types for binary operator \n");
									exit(1);
									
								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								
							}
						
						break;
					 
					
					}
		
			
			 
			 
		break;
		case REGISTER:  
			
			switch(rhs->typos){
						
						case INT:
						
							switch(lhs){
								
								case astInt:
								
									 fprintf(text,"push dword [rgs]\n");
									 
								break;
								case astReal:
									
									
									 fprintf(text,"fild dword [rgs]\n");
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");
									
								break;
								case astBool:
									printf("Error: bad operand types for binary operator \n");
									exit(1);
								break;
								
							}
						
						break;
						case REAL:
						
							switch(lhs){
									
									case astInt:
										 fprintf(text,"fld qword [frgs]\n");
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");
										 
									break;
									case astReal:
										
										 fprintf(text,"fld qword [frgs]\n");
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");
										
									break;
									case astBool:
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									break;
									
								}
						
						
						break;
						case BOOL:
						
							switch(lhs){
								
								case astInt:
								
									    printf("Error: bad operand types for binary operator \n");
										exit(1);
									 
								break;
								case astReal:
									
										printf("Error: bad operand types for binary operator \n");
										exit(1);
									
								break;
								case astBool:
										fprintf(text,"push dword [rgs]\n");
								break;
								
							}
						
						break;
					 
					
					}
			 
			
			
		break;
		case STACK:
		
			 fprintf(text,"ERROR DECLASSIGN[MEMORY-STACK]\n");
			 
		break;
		
		
	}
	
	//Code Generation for next variables
	CodeGeneration(p->pAstNode[2],lev+1,lvalue,0);
	
}

//Variables
void ProcessVarsSeq(AstNode *p,int lev,int lvalue,int leftChild) {
	
	symbol * lhs;
	lhs  = p->SymbolNode;

	switch(lhs->typos){
		
		case INT:
				
				//Variable Declaration
				fprintf(text,"push 0\n");
		break;
		case REAL:
				
				fprintf(text,"fldz\n");
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fstp qword [esp]\n");
			
		break;
		case BOOL:
				
				//Variable Declaration
				fprintf(text,"push 0\n");
		break;
		
		
	}
	
	
	
	
	
	//Code Generation for next variables
	CodeGeneration(p->pAstNode[0],lev+1,lvalue,0);
	
} 

//Variable Assign
void ProcessVarAssign(AstNode *p,int lev){
	
	symbol *lhs, *rhs;
	
	lhs = p -> SymbolNode;

	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();
	
	
	switch(rhs->sclass){
		
		case CONSTANT:
			
			switch(rhs->typos){
				
				case INT:
				
					switch(lhs->typos){
						
						case INT:
						
							 fprintf(text,"push %d\n",rhs->timi);
							 
					    break;
						case REAL:
							
							 fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
							 fprintf(text,"fld dword [INT_%d]\n",NUM_OF_INT_CONST++);
							 fprintf(text,"sub esp,8\n");
							 fprintf(text,"fstp qword [esp]\n");
							
						break;
						case BOOL:
						
							printf("Error: bad operand types for binary operator \n");
							exit(1);
							 
					    break;
						
					}
				
				break;
				case REAL:
				
					switch(lhs->typos){
							
							case INT:
								
								 fprintf(text,"push %d\n",(int) rhs->dtimi);
								 
							break;
							case REAL:
								
								 fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
								 fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
								 fprintf(text,"sub esp,8\n");
								 fprintf(text,"fstp qword [esp]\n");
								
							break;
							case BOOL:
						
								printf("Error: bad operand types for binary operator \n");
								exit(1);
							 
							break;
							
						}
				
				
				break;
				case BOOL:
				
					switch(lhs->typos){
						
						case INT:
						
							 printf("Error: bad operand types for binary operator \n");
							 exit(1);
							 
					    break;
						case REAL:
							
							 printf("Error: bad operand types for binary operator \n");
							 exit(1);
							
						break;
						case BOOL:
						
							 fprintf(text,"push %d\n",rhs->timi);
							 
					    break;
						
					}
				
				break;
			 
			
			}
		break;
		case MEMORY:
		
				switch(rhs->typos){
						
						case INT:
						
							switch(lhs->typos){
								
								case INT:
								
									 fprintf(text,"push dword [%s]\n",rhs->pseudonym);
									 
								break;
								case REAL:
									
									
									 fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");
									
								break;
								case BOOL:
							
									 printf("Error: bad operand types for binary operator \n");
									 exit(1);
							
								break;
								
							}
						
						break;
						case REAL:
						
							switch(lhs->typos){
									
									case INT:
										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");
										 
									break;
									case REAL:
										
										 fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");
										
									break;
									case BOOL:
							
										 printf("Error: bad operand types for binary operator \n");
										 exit(1);
							
									break;
									
								}
						
						
						break;
						case BOOL:
						
							switch(lhs->typos){
								
								case INT:
								
									 printf("Error: bad operand types for binary operator \n");
									 exit(1);
									 
								break;
								case REAL:
									
									 printf("Error: bad operand types for binary operator \n");
									 exit(1);
									
								break;
								case BOOL:
							
									  fprintf(text,"push dword [%s]\n",rhs->pseudonym);
							
								break;
								
							}
						
						break;
					 
					
					}
		
			
			 
			 
		break;
		case REGISTER:  
			
			switch(rhs->typos){
						
						case INT:
						
							switch(lhs->typos){
								
								case INT:
								
									 fprintf(text,"push dword [rgs]\n");
									 
								break;
								case REAL:
									
									
									 fprintf(text,"fild dword [rgs]\n");
									 fprintf(text,"sub esp,8\n");
									 fprintf(text,"fstp qword [esp]\n");
									
								break;
								case BOOL:
							
										 printf("Error: bad operand types for binary operator \n");
										 exit(1);
							
								break;
							}
						
						break;
						case REAL:
						
							switch(lhs->typos){
									
									case INT:
										 fprintf(text,"fld qword [frgs]\n");
										 //fprintf(text,"fldcw [cw]\n");
										 fprintf(text,"fistp dword [esp]\n");
										 
									break;
									case REAL:
										
										 fprintf(text,"fld qword [frgs]\n");
										 fprintf(text,"sub esp,8\n");
										 fprintf(text,"fstp qword [esp]\n");
										
									break;
									case BOOL:
							
										 printf("Error: bad operand types for binary operator \n");
										 exit(1);
							
									break;
								}
						
						
						break;
						case BOOL:
						
							switch(lhs->typos){
								
								case BOOL:
								
									 fprintf(text,"push dword [rgs]\n");
									 
								break;
								case REAL:
									
									  printf("Error: bad operand types for binary operator \n");
									  exit(1);
									
								break;
								case INT:
								
									  printf("Error: bad operand types for binary operator \n");
									  exit(1);
							
								break;
							}
						
						break;
					 
					
					}
			 
			
			
		break;
		case STACK:
		
			 fprintf(text,"ERROR DECLASSIGN[MEMORY-STACK]\n");
			 
		break;
		
		
	}
	
	//Code Generation for next variables
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
}

//Parameters
void ProcessParamSeq(AstNode *p,int lev,int lvalue,int leftChild){
	
	//Code Generation for previous parameters
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	
	switch(p->SymbolNode->typos){
		
		case INT:
			BYTES_OF_PARAMETERS +=4;
		break;
		case REAL:
			BYTES_OF_PARAMETERS +=8;
		break;
		case BOOL:
			BYTES_OF_PARAMETERS +=4;
		break;
	}
	push_vs(p->SymbolNode);
	
}

//Formals
void ProcessFormalsSeq(AstNode *p,int lev,int lvalue,int leftChild){
	
	//Code Generation for previous parameters
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	
	switch(p->SymbolNode->typos){
		
		case INT:
			BYTES_OF_PARAMETERS +=4;
		break;
		case REAL:
			BYTES_OF_PARAMETERS +=8;
		break;
		case BOOL:
			BYTES_OF_PARAMETERS +=4;
		break;
	}
	
	push_vs(p->SymbolNode);
	
}


//Actuals
void  ProcessActuals(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;
	
	
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	rhs = pop_vs();
	
	if(rhs->sclass == MEMORY){
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push dword [%s]\n",rhs->pseudonym);
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push dword [%s]\n",rhs->pseudonym);
			 break;						 
		}
		
		
		
	}
	else if (rhs->sclass == CONSTANT){
		
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push %d\n",rhs->timi);
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
				fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push %d\n",rhs->timi);
			 break;
									 
		}
		
		
		
	}
	else if (rhs->sclass == REGISTER){
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push dword [rgs]\n");
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fld qword [frgs]\n");
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push dword [rgs]\n");
			 break;						 
		}
		
		
		
		
	}else{
		
		fprintf(text,"ERROR ACTUALS[STACK]\n");
		
	}
	
	//Code Generation for previous argument expressions
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	
}

//Args
void  ProcessArgsSeq(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;
	
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[1],lev+1,0,0);
	rhs = pop_vs();
	
	
	if(rhs->sclass == MEMORY){
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push dword [%s]\n",rhs->pseudonym);
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push dword [%s]\n",rhs->pseudonym);
			 break;						 
		}
		
		
		
	}
	else if (rhs->sclass == CONSTANT){
		
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push %d\n",rhs->timi);
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
				fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push %d\n",rhs->timi);
			 break;		
			 
		}
		
		
		
	}
	else if (rhs->sclass == REGISTER){
		
		 switch(rhs->typos){
									 
									 
			 case INT:
				fprintf(text,"push dword [rgs]\n");
			 break;
			 case REAL:
				fprintf(text,"sub esp,8\n");
				fprintf(text,"fld qword [frgs]\n");
				fprintf(text,"fstp qword [esp]\n");
			 break;
			 case BOOL:
				fprintf(text,"push dword [rgs]\n");
			 break;						 
		}
		
		
		
		
	}else{
		
		fprintf(text,"ERROR ARGS[STACK]\n");
		
	}
	
	//Code Generation for previous argument expressions
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
}


//Return Statement
void ProcessReturnStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();
	
	
	
	if(rhs->sclass == MEMORY){
		
		 switch(rhs->typos){
									 
			case INT:
				//Push 
				fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
			break;
			case REAL:
				//Push 
				fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
			break;
			case BOOL:
				//Push 
				fprintf(text,"fild dword [%s]\n",rhs->pseudonym);
			break;
									 
		}
		
	
	}
	else if (rhs->sclass == CONSTANT){
		
		 switch(rhs->typos){
									 
			case INT:
			
				//Push 
				fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
				fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

			break;
			case REAL:
			
				fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
				fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
				
			break;
			case BOOL:
			
				//Push 
				fprintf(data,"INT_%d dd %d\n",NUM_OF_INT_CONST,rhs->timi);
				fprintf(text,"fild dword [INT_%d]\n",NUM_OF_INT_CONST++);

			break;
									 
		}
		
	    
	}
	else if (rhs->sclass == REGISTER){
		
	     switch(rhs->typos){
									 
			case INT:
				//Push 
				fprintf(text,"fild dword [rgs]\n");
			break;
			case REAL:
				//Push 
				fprintf(text,"fld qword [frgs]\n");
			break;
			case BOOL:
				//Push 
				fprintf(text,"fild dword [rgs]\n");
			break;
									 
		}
		
		
	}
	else{ /*--- STACK ---*/
		
		fprintf(text,"ERROR RETURN[STACK]\n");
	}
	
	fprintf(text,"mov esp,ebp\n");
	fprintf(text,"pop ebp\n");
	fprintf(text,"ret %d\n",BYTES_OF_PARAMETERS);
}



//Print Number Statement
void ProcessPrintStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();
	
	
	
	if(rhs->sclass == MEMORY){
		
		switch (rhs->typos){
			
			case BOOL:
					
					fprintf(text,"push dword [%s]\n",rhs->pseudonym);
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			
			case INT:
					
					fprintf(text,"push dword [%s]\n",rhs->pseudonym);
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
					
					fprintf(text,"sub esp,8\n");
				    fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_print_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
	
	}
	else if (rhs->sclass == CONSTANT){
		
		switch (rhs->typos){
			
			case BOOL:
					
					fprintf(text,"push %d\n",rhs->timi);
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case INT:
					
					fprintf(text,"push %d\n",rhs->timi);
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
			
					fprintf(text,"sub esp,8\n");
					fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
					fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
					
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_print_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
		
	    
	}
	else if (rhs->sclass == REGISTER){
		
		
		switch (rhs->typos){
			
			case BOOL:
		
					fprintf(text,"push dword [rgs]\n");
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			
			case INT:
		
					fprintf(text,"push dword [rgs]\n");
					fprintf(text,"push format_print_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
				
					fprintf(text,"sub esp,8\n");
				    fprintf(text,"fld qword [frgs]\n");
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_print_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
		
	    
		
		
		
	}
	else{ /*--- STACK ---*/
		
		fprintf(text,"ERROR RETURN[STACK]\n");
	}
	
}

//PrintLn Number Statement
void ProcessPrintLnStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;
	
	//Code Generation for expression
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();
	
	
	if(rhs->sclass == MEMORY){
		
		switch (rhs->typos){
			
			case BOOL:
		
					fprintf(text,"push dword [%s]\n",rhs->pseudonym);
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			
			case INT:
		
					fprintf(text,"push dword [%s]\n",rhs->pseudonym);
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
				
					fprintf(text,"sub esp,8\n");
				    fprintf(text,"fld qword [%s]\n",rhs->pseudonym);
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_println_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
	
	}
	else if (rhs->sclass == CONSTANT){
		
		switch (rhs->typos){
			
			case BOOL:
		
					fprintf(text,"push %d\n",rhs->timi);
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			
			case INT:
		
					fprintf(text,"push %d\n",rhs->timi);
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
			
					fprintf(text,"sub esp,8\n");
					
					fprintf(data,"REAL_%d dq %lf\n",NUM_OF_REAL_CONST,rhs->dtimi);
					fprintf(text,"fld qword [REAL_%d]\n",NUM_OF_REAL_CONST++);
					
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_println_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
		
	    
	}
	else if (rhs->sclass == REGISTER){
		
		
		switch (rhs->typos){
			
			case BOOL:
		
					fprintf(text,"push dword [rgs]\n");
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			
			case INT:
		
					fprintf(text,"push dword [rgs]\n");
					fprintf(text,"push format_println_int\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 8\n");
			break;
			case REAL:
				
					fprintf(text,"sub esp,8\n");
				    fprintf(text,"fld qword [frgs]\n");
					fprintf(text,"fstp qword [esp]\n");
					fprintf(text,"push format_println_real\n");
					fprintf(text,"call _printf\n");
					fprintf(text,"add esp, 12\n");
		
			break;
		
		}
		
	    
		
		
		
	}
	else{ /*--- STACK ---*/
		
		fprintf(text,"ERROR RETURN[STACK]\n");
	}
	
}
 
 
 void ProcessLiteralStmt(AstNode *p,int lev,int lvalue,int leftChild){
	 
	
	 fprintf(data,"LTRL_%d: db %s,0\n",NUM_OF_LITERALS,p->SymbolNode->name);
	 
	 
 }
 
  void ProcessLiteralLnStmt(AstNode *p,int lev,int lvalue,int leftChild){
	 
	
	 fprintf(data,"LTRL_%d: db %s,10,0\n",NUM_OF_LITERALS,p->SymbolNode->name);
	 
	 
 }
	 


//Print Literal Statement
void ProcessPrintLtStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;

	//Code Generation for literal
	ProcessLiteralStmt(p,lev+1,0,0);

	fprintf(text,"push LTRL_%d\n",NUM_OF_LITERALS);
	NUM_OF_LITERALS++;
	
    fprintf(text,"call _printf\n");
    fprintf(text,"add  esp, 4\n");
	
}

//Println Literal Statement
void ProcessPrintLnLtStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *rhs;

	//Code Generation for literal
	ProcessLiteralLnStmt(p,lev+1,0,0);

	fprintf(text,"push LTRL_%d\n",NUM_OF_LITERALS);
	NUM_OF_LITERALS++;
	
    fprintf(text,"call _printf\n");
    fprintf(text,"add  esp, 4\n");
	
}


void ProcessPutsStmt(AstNode *p,int lev,int lvalue,int leftChild){
		 
	symbol *rhs;
    
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	
	 
}

void ProcessExprInline(AstNode *p,int lev,int lvalue,int leftChild){
	
	 ProcessPrintStmt(p,lev+1,0,0);
	 CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
}

void ProcessLiteralInline(AstNode *p,int lev,int lvalue,int leftChild){
	
	 ProcessPrintLtStmt(p,lev+1,0,0);
	 CodeGeneration(p->pAstNode[0],lev+1,0,0);
	
}

void ProcessSingleExprInline(AstNode *p,int lev,int lvalue,int leftChild){
	
	 ProcessPrintLnStmt(p,lev+1,0,0);
	 //CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
}

void ProcessSingleLiteralInline(AstNode *p,int lev,int lvalue,int leftChild){
	
	  ProcessPrintLnLtStmt(p,lev+1,0,0);
	 //CodeGeneration(p->pAstNode[1],lev+1,0,0);
	
}
 
 //Read Statement
void ProcessReadStmt(AstNode *p,int lev,int lvalue,int leftChild){
	
	symbol *lhs, *rhs;
	
	//Code Generation for literal
	ProcessLiteralStmt(p,lev+1,0,0);

	fprintf(text,"push LTRL_%d\n",NUM_OF_LITERALS);
	NUM_OF_LITERALS++;
	
    fprintf(text,"call _printf\n");
    fprintf(text,"add  esp, 4\n");
	
	//Code Generation for location
	CodeGeneration(p->pAstNode[0],lev+1,0,0);
	rhs = pop_vs();
	
	
	
	if(rhs->sclass == MEMORY){
		
		switch(rhs->sclass){
			
			case INT:
			
					fprintf(text,"lea eax, [%s]\n",rhs->pseudonym);
					fprintf(text,"push eax\n");
					fprintf(text,"push format_read_int\n");
					fprintf(text,"call _scanf\n");
					fprintf(text,"add esp, 8\n");
					
			break;
			case REAL:
					fprintf(text,"lea eax, [%s]\n",rhs->pseudonym);
					fprintf(text,"push eax\n");
					fprintf(text,"push format_read_real\n");
					fprintf(text,"call _scanf\n");
					fprintf(text,"add esp, 8\n");
			
			break;
	
		
	
	}
	
	}
}
 
 /* ------------------------------------------------------------------------ */
  
  
/* CodeGeneration */

void CodeGeneration(AstNode *p, int lev, int lvalue, int leftChild)
{  

    switch (p->NodeType)
      {
         case astEmptyProgram: 
         break;
		 //case astLibList: 
            // ProcessLibList(p,lev,0);
        // break;
		// case astEmptyLib: 
             
        // break;
		 //case astLib: 
             //ProcessLib(p,lev,0);
        // break;
         case astProgram: 
             ProcessProgram(p,lev);
         break;
         case astMethSeq: 
             ProcessMethSeq(p,lev); 
         break;
         case astMethLast: 
             ProcessMethLast(p,lev); 
         break;
         case astParamSeq: 
             ProcessParamSeq(p,lev,lvalue,leftChild); 
         break;
         case astParamEmpty: 
             //ProcessParamEmpty(p,lev,lvalue,leftChild);  
         break;
         case astFormalsSeq: 
             ProcessFormalsSeq(p,lev,lvalue,leftChild);  
         break;
         case astFormalsEmpty: 
             //ProcessFormalsEmpty(p,lev,lvalue,leftChild);
         break;
         case astInt: 
             //ProcessInt(p,lev,lvalue,leftChild); 
         break;  
		 case astReal: 
             //ProcessReal(p,lev,lvalue,leftChild); 
         break;		 
		 case astIfStmt: 
		     ProcessIfStmt(p,lev,lvalue,leftChild);
         break;
         case astIfElseStmt: 
             ProcessIfElseStmt(p,lev,lvalue,leftChild);
         break;
		 case astSingleIfStmt:
			 ProcessSingleIfStmt(p,lev,lvalue,leftChild);
		 break;
		 case astSingleUnlessStmt:
			 ProcessSingleUnlessStmt(p,lev,lvalue,leftChild);
		 break;
         case astBody: 
             ProcessBody(p,lev);
         break;
         case astDeclsSeq: 
             ProcessDeclsSeq(p,lev,lvalue,leftChild);
         break;
         case astDeclsEmpty: 
             //ProcessDeclsEmpty(p,lev,lvalue,leftChild);
         break;
         case astDeclListSeq:
             ProcessDeclListSeq(p,lev,lvalue,leftChild); 
         break;
         case astDeclListEmpty: 
             //ProcessDeclListEmpty(p,lev,lvalue,leftChild); 
         break;
         case astDecl: 
             ProcessDecl(p,lev,lvalue,leftChild);
         break;
         case astDeclAssign: 
             ProcessDeclAssign(p,lev,lvalue,leftChild);
         break;
         case astVarsSeq: 
             ProcessVarsSeq(p,lev,lvalue,leftChild);
         break;
         case astVarAssign:
             ProcessVarAssign(p,lev);
         break;
         case astVarEmpty: 
             //ProcessVarEmpty(p,lev,lvalue,leftChild);
         break;
         case astStmtSeq: 
             ProcessStmtSeq(p,lev);
         break;
         case astStmtEmpty: 
             //ProcessStmtEmpty(p,lev,lvalue,leftChild);
         break;
         case astLocation: 
             ProcessLocation(p);
         break;
         case astReturnStmt:
             ProcessReturnStmt(p,lev,lvalue,leftChild);
         break;
         case astMethodName: 
             //ProcessMethodName(p,lev,lvalue,leftChild);
         break;
         case astWhileStmt: 
             ProcessWhileStmt(p,lev,lvalue,leftChild);
         break;
		 case astTimesStmt: 
             ProcessTimesStmt(p,lev,lvalue,leftChild);
         break;
         case astBreakStmt: 
             ProcessBreakStmt();
         break;
		 case astPutsStmt:
			  ProcessPutsStmt(p,lev,lvalue,leftChild);
		 break;
		 case astExprInline:
			  ProcessExprInline(p,lev,lvalue,leftChild);
		 break;
		 case astLiteralInline:
			  ProcessLiteralInline(p,lev,lvalue,leftChild);
		 break;
		 case astSingleExprInline:
			  ProcessSingleExprInline(p,lev,lvalue,leftChild);
		 break;
		 case astSingleLiteralInline:
			  ProcessSingleLiteralInline(p,lev,lvalue,leftChild);
		 break;
		 case astPrintStmt:
			 ProcessPrintStmt(p,lev,lvalue,leftChild);
		 break;
		 case astPrintLnStmt:
			 ProcessPrintLnStmt(p,lev,lvalue,leftChild);
		 break;
		 case astReadStmt:
			ProcessReadStmt(p,lev,lvalue,leftChild);
		 break;
		 case astPrintLtStmt:
			 ProcessPrintLtStmt(p,lev,lvalue,leftChild);
		 break;
		 case astPrintLnLtStmt:
			 ProcessPrintLnLtStmt(p,lev,lvalue,leftChild);
		 break;
		 case astExprStmt:
			 ProcessExprStmt(p,lev,lvalue,leftChild);
		 break;
		 case astNotExpr: 
             ProcessNotExpr(p,lev,lvalue,leftChild);
         break;
		 case astAndExpr: 
             ProcessAndExpr(p,lev,lvalue,leftChild);
         break;
		 case astOrExpr: 
             ProcessOrExpr(p,lev,lvalue,leftChild);
         break;
         case astCompExpr: 
             ProcessCompExpr(p,lev,lvalue,leftChild);
         break;
		 case astAddAssign: 
             ProcessAddAssign(p,lev,0);
         break;
		 case astSubAssign: 
             ProcessSubAssign(p,lev,0);
         break;
         case astAssign: 
			 ProcessUniqueAssign(p,lev,0);
             //ProcessAssign(p,lev,0);
         break;
		 case astAssignSeq:
			 ProcessAboveMultiAssignSeq(p,lev,0);
			 //ProcessAssignSeq(p,lev,0);
		 break;
		 case astListedAssign:
			 ProcessListedAssign(p,lev,0);
		 break;
		 case astNestedAssign:
			 ProcessNestedAssign(p,lev,0);
		 break;
		 case astEmbedAssign:
			 ProcessEmbedAssign(p,lev,0);
		 break;
         case astAddExpr: 
             ProcessAddExpr(p,lev,lvalue,leftChild);
         break;
         case astAddExprLast: 
             //ProcessAddExprLast(p,lev,lvalue,leftChild);
         break;
         case astNullStmt: 
             //ProcessNullStmt(p,lev,lvalue,leftChild);
         break;
         case astMethodCall: 
             ProcessMethodCall(p,lev,lvalue,leftChild);
         break;
         case astGeOp: 
             //ProcessGeOp(p,lev,lvalue,leftChild);
         break;
         case astGOp: 
             //ProcessGOp(p,lev,lvalue,leftChild);
         break;
         case astLeOp: 
             //ProcessLeOp(p,lev,lvalue,leftChild); 
         break;
		 case astLOp: 
             //ProcessLOp(p,lev,lvalue,leftChild);
         break;
		 case astNeOp: 
             //ProcessNeOp(p,lev,lvalue,leftChild);
         break;
		 case astEOp: 
             //ProcessEOp(p,lev,lvalue,leftChild);
         break;
		 case astAddOp: 
             //ProcessAddOp(p,lev,lvalue,leftChild);
         break;
		 case astSubOp: 
             //ProcessSubOp(p,lev,lvalue,leftChild);
         break;
		 case astMulExpr: 
             ProcessMulExpr(p,lev,lvalue,leftChild);
         break;
		 case astMulOp: 
             //ProcessMulOp(p,lev,lvalue,leftChild);
         break;
		 case astDivOp: 
             //ProcessDivOp(p,lev,lvalue,leftChild);
         break;
		 case astModOp: 
             //ProcessModOp(p,lev,lvalue,leftChild);
         break;
		 case astRealDeConst: 
             ProcessRealDeConst(p);
         break;
		 case astDeConst: 
             ProcessDeConst(p);
         break;
		 case astTrue: 
             ProcessTrue(p);
         break;
		 case astIncreaseAfter:
			 ProcessIncreaseAfter(p,lev,leftChild);
		 break;
		 case astIncreaseBefore:
			 ProcessIncreaseBefore(p,lev,leftChild);
		 break;
		 case astDecreaseAfter:
			 ProcessDecreaseAfter(p,lev,leftChild);
		 break;
		 case astDecreaseBefore:
			 ProcessDecreaseBefore(p,lev,leftChild);
		 break;
		 case astActualsEmpty: 
             //ProcessActualsEmpty(p,lev,lvalue,leftChild); 
         break;
		 case astFalse: 
             ProcessFalse(p);
         break;
		 case astActuals: 
             ProcessActuals(p,lev,lvalue,leftChild);
         break;
		 case astArgsSeq: 
             ProcessArgsSeq(p,lev,lvalue,leftChild); 
         break;
		 case astArgsEmpty: 
             //ProcessArgsEmpty(p,lev,lvalue,leftChild); 
         break;
         default: 
            fprintf(text,"Unknown=%d\n",p->NodeType);
      }
}



void BeforeCodeGeneration(){
	
	fprintf(data,"[BITS 32]\n");
	
	fprintf(text,"global    _main\n");
	
	fprintf(data,"    section .data\n\n");
	fprintf(data,"rgs    dd    0\n");
	fprintf(data,"frgs    dq    0\n");
	fprintf(data,"cw dw 043fH\n");
	
	fprintf(data,"format_print_int    db    \"%%d\",0\n");
	fprintf(data,"format_println_int    db    \"%%d\",10,0\n");
	fprintf(data,"format_print_real    db    \"%%0.4lf\",0\n");
	fprintf(data,"format_println_real    db    \"%%0.4lf\",10,0\n");
	fprintf(data,"format_read_int    db    \"%%d\", 0\n");
	fprintf(data,"format_read_real    db    \"%%lf\", 0\n");
	fprintf(data,"extern    _scanf\n");
	fprintf(data,"extern    _printf\n");
	
	fprintf(text,"    section .text\n\n");
	

	
}

void AfterCodeGeneration(){

     //fprintf(text,"\n\nSTART EQU *\n");
	 //fprintf(text,"JMP MAIN\n");
	 //fprintf(text,"OVERFLOW HLT\n");
     //fprintf(text,"UNDERFLOW HLT\n");
	// fprintf(text,"TOOLARGE  HLT\n");
	 //fprintf(text,"DIVBYZERO  HLT\n");
     //fprintf(text,"END START\n");
}

void main(void)
{  

   AstNode *p;
   int wrong,i;
   
   Init_Hash_Table();
   Init_Array_Hash_Table();
   Init_while_stack();
   wrong=yyparse();
   if(!wrong) 
   {
      p=TreeRoot;
      //traverse(p,-3);
     
      text=fopen("text.asm","w");
	  data=fopen("data.asm","w");
	  BeforeCodeGeneration();
      CodeGeneration(p,0,0,0);
	  AfterCodeGeneration();
      fclose(text);
	  fclose(data);
	  
	  system("copy data.asm + text.asm program.asm");
	  system("del data.asm");
	  system("del text.asm");
	 
	 
   }
}


