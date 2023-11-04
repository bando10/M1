grammar PP;

// ruleName
//     : subrule { action } ;

//Type
type returns [Type value]:
    a = array {$value = $a.value}
    | t = typeBase {$value = $t.value};

array returns [Type value]:
    'array of' t = typeBase {$value = new Array($t.value)};

typeBase returns [Type value]:
    'integer' {$value = new Int();}
    | 'boolean' {$value = new Bool();};

 // COnstantes

const returns [PPExpr value]:
    n = num {$value = $n.value;}
    | t = true {$value = $t.value;}
    | f = false {$value = $f.value;};

num returns [PPExpr value]:
    n = NUM {$value = new PPCte(Integer.parseInt($n.text))};

true returns [PPExpr value] :
    'true' {$value = new PPTrue();} ;

false returns [PPExpr value] :
    'false' {$value = new PPFalse();} ;


//Operateurs unaires
unOp returns [PPExpr value]:
    i = inv {$value = $i.value;}
    | n = not {$value = $n.value;};


inv returns [PPInv value]:
    '-' e = exprNum {$value = new PPInv($e.value);};

not returns [PPExpr value] :
    'not' e = exprBool {$value = new PPNot($e.value);};


//Operateurs binaires

binOp returns [PPExpr value]:
   a = add
    | s = sub {$value = $s.value;}
    | m = mul {$value = $m.value;}
    | d = div {$value = $d.value;}
    | an = and {$value = $an.value;}
    | o = or {$value = $o.value;}
    | l = lt {$value = $l.value;}
    | lo = loe {$value = $lo.value;}
    | e = eq {$value = $e.value;}
    | g = goe {$value = $g.value;}
    | t = gt {$value = $t.value;};

add returns [PPExpr value] :
    a = exprNum '+' b = expr {$value = new PPAdd($a.value, $b.value);};
sub returns [PPExpr value] :
    a = exprNum '-' b = expr {$value = new PPSub($a.value, $b.value);};
mul returns [PPExpr value] :
    a = exprNum '*' b = expr {$value = new PPMul($a.value, $b.value);};
div returns [PPExpr value] :
    a = exprNum '/' b = expr {$value = new PPDiv($a.value, $b.value);};
and returns [PPExpr value] :
    a = exprNum 'and' b = expr {$value = new PPAnd($a.value, $b.value);};
or returns [PPExpr value] :
    a = exprNum 'or' b = expr {$value = new PPOr($a.value, $b.value);};
lt returns [PPExpr value] :
    a = exprNum '<' b = expr {$value = new PPLt($a.value, $b.value);};
loe returns [PPExpr value] :
    a = exprNum '<=' b = expr {$value = new PPLe($a.value, $b.value);};
eq returns [PPExpr value] :
    a = exprNum '=' b = expr {$value = new PPEq($a.value, $b.value);};
goe returns [PPExpr value] :
    a = exprNum '>=' b = expr {$value = new PPGe($a.value, $b.value);};
gt returns [PPExpr value] :
    a = exprNum '>' b = expr {$value = new PPGt($a.value, $b.value);};

// Cible d'appels

funCall returns [PPExpr value] :
    f = callee '(' e = expr ')' {$value = new PPFunCall($f.value, new ArrayList<PPExpr>() {});} |
    f = callee '()' {$value = new PPFunCall($f.value, new ArrayList<PPExpr>() {});};


callee returns [Callee value]:
    r = read {$value = $r.value;}
    | w = write {$value = $w.value;}
    | fu = funcName {$value = $fu.value;};

read returns [Callee value] :
    'read' {$value = new Read();} ;

write returns [Callee value] :
    'write' {$value = new Write();} ;

funcName returns [Callee value] :
    f = ID {$value = new User(new String("$f.text"));} ;

// Tableau

tabGet returns [PPExpr value] :
    n = varName '[' e = exprNum ']' {$value = new PPArrayGet($n.value, $e.value);} ;

alloc returns [PPExpr value] :
    'new array of' t = type '[' e = exprNum ']' {$value = new PPArrayAlloc($t.value, $e.value);} ;


// Expressions
exprNum returns [PPExpr value] :
    NUM
    | v = varName {$value = $v.value;}
    | fu = funCall {$value = $fu.value;}
    | t = tabGet {$value = $t.value;};

exprBool returns [PPExpr value] :
    t = true {$value = $t.value;}
    | f = false {$value = $f.value;}
    | v = varName {$value = $v.value;}
    | fu = funCall {$value = $fu.value;}
    | ta = tabGet {$value = $ta.value;};

expr returns [PPExpr value] :
    c = const {$value = $c.value;}
    | v = varName {$value = $v.value;}
    | b = binOp {$value = $b.value;}
    | u = unOp {$value = $u.value;}
    | f = funCall {$value = $f.value;}
    | t = tabGet {$value = $t.value;}
    | a = alloc {$value = $a.value;} ;

varName returns [PPExpr value] :
    n = ID {$value = new PPVar( new String("$n.text") );} ;

 // Instructions

 assignVar returns [PPInst value] :
     v = ID ':=' e = expr {$value = new PPAssign(new String("$v.text"), $e.value); } ;

 assignTab returns [PPInst value] :
     e0 = expr '[' e1 = expr '] :=' e2 = expr {$value = new PPArraySet($e0.value, $e1.value, $e2.value); } ;

 if returns [PPInst value] :
     'if' e = expr 'then' i1 = instru 'else' i2 = instru
     {$value =  new PPCond($e.value, $i1.value, $i2.value);} ;

 while returns [PPInst value] :
     'while' e = expr 'do' i = instr
     {$value =  new PPWhile($e.value, $i.value);} ;

 processCall returns [PPInst value] :
     f = callee '(' e = expr ')' {$value = new PPProcCall($f.value, new ArrayList<PPExpr>() {});} ;

 skipInstr returns [PPInst value] :
     'skip' {$value = new PPSkip(); } ;

 seq returns [PPInst value] :
     i1 = instr ';' i2 = instru {$value = new PPSeq($i1.value, $i2.value); } ;

 instr returns [PPInst value] :
     v = assignVar {$value = $v.value;}
     | t = assignTab {$value = $t.value;}
     | i = if {$value = $i.value;}
     | w = while {$value = $w.value;}
     | p = processCall {$value = $p.value;}
     | s = skipInstr {$value = $s.value;};
     /*| e = seq {$value = $e.value;} */

instru returns [PPInst value] :
    i0 = instr {$value = $i0.value;}
    | i1 = seq {$value = $i1.value;} ;


// Process

declaration returns [Pair value] :
    'var' p = pair {$value = $p.value;} ;

pair returns [Pair value] :
    x = ID ':' t = type {$value = new Pair(new String("$x.text"), $t.value);} ;

function returns [PPFun value] :
    n = ID '(' p0 = pair ') :' t1 = type
    (d = declaration)+
    i = instr
    {$value = new PPFun(new String("$n.text"), new ArrayList<Pair<String,Type>>(), new ArrayList<Pair<String,Type>>(), $i.value, $t1.value);} ;


// Program


program returns [PPProg value] :
    (d = declaration)+
    (f = function)*
    i = instr
    {$value = new PPProg(new ArrayList<Pair<String,Type>>(), new ArrayList<PPDef>(), $i.value); } ;






ID : [a-zA-Z][a-zA-Z0-9]* ;             // match lower-case identifiers
NUM : ('0'..'9')+ ;

WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
