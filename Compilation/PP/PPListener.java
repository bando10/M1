// Generated from PP.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link PPParser}.
 */
public interface PPListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link PPParser#type}.
	 * @param ctx the parse tree
	 */
	void enterType(PPParser.TypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#type}.
	 * @param ctx the parse tree
	 */
	void exitType(PPParser.TypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#array}.
	 * @param ctx the parse tree
	 */
	void enterArray(PPParser.ArrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#array}.
	 * @param ctx the parse tree
	 */
	void exitArray(PPParser.ArrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#typeBase}.
	 * @param ctx the parse tree
	 */
	void enterTypeBase(PPParser.TypeBaseContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#typeBase}.
	 * @param ctx the parse tree
	 */
	void exitTypeBase(PPParser.TypeBaseContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#const}.
	 * @param ctx the parse tree
	 */
	void enterConst(PPParser.ConstContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#const}.
	 * @param ctx the parse tree
	 */
	void exitConst(PPParser.ConstContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#num}.
	 * @param ctx the parse tree
	 */
	void enterNum(PPParser.NumContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#num}.
	 * @param ctx the parse tree
	 */
	void exitNum(PPParser.NumContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#true}.
	 * @param ctx the parse tree
	 */
	void enterTrue(PPParser.TrueContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#true}.
	 * @param ctx the parse tree
	 */
	void exitTrue(PPParser.TrueContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#false}.
	 * @param ctx the parse tree
	 */
	void enterFalse(PPParser.FalseContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#false}.
	 * @param ctx the parse tree
	 */
	void exitFalse(PPParser.FalseContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#unOp}.
	 * @param ctx the parse tree
	 */
	void enterUnOp(PPParser.UnOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#unOp}.
	 * @param ctx the parse tree
	 */
	void exitUnOp(PPParser.UnOpContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#inv}.
	 * @param ctx the parse tree
	 */
	void enterInv(PPParser.InvContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#inv}.
	 * @param ctx the parse tree
	 */
	void exitInv(PPParser.InvContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#not}.
	 * @param ctx the parse tree
	 */
	void enterNot(PPParser.NotContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#not}.
	 * @param ctx the parse tree
	 */
	void exitNot(PPParser.NotContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#binOp}.
	 * @param ctx the parse tree
	 */
	void enterBinOp(PPParser.BinOpContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#binOp}.
	 * @param ctx the parse tree
	 */
	void exitBinOp(PPParser.BinOpContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#add}.
	 * @param ctx the parse tree
	 */
	void enterAdd(PPParser.AddContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#add}.
	 * @param ctx the parse tree
	 */
	void exitAdd(PPParser.AddContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#sub}.
	 * @param ctx the parse tree
	 */
	void enterSub(PPParser.SubContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#sub}.
	 * @param ctx the parse tree
	 */
	void exitSub(PPParser.SubContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#mul}.
	 * @param ctx the parse tree
	 */
	void enterMul(PPParser.MulContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#mul}.
	 * @param ctx the parse tree
	 */
	void exitMul(PPParser.MulContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#div}.
	 * @param ctx the parse tree
	 */
	void enterDiv(PPParser.DivContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#div}.
	 * @param ctx the parse tree
	 */
	void exitDiv(PPParser.DivContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#and}.
	 * @param ctx the parse tree
	 */
	void enterAnd(PPParser.AndContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#and}.
	 * @param ctx the parse tree
	 */
	void exitAnd(PPParser.AndContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#or}.
	 * @param ctx the parse tree
	 */
	void enterOr(PPParser.OrContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#or}.
	 * @param ctx the parse tree
	 */
	void exitOr(PPParser.OrContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#lt}.
	 * @param ctx the parse tree
	 */
	void enterLt(PPParser.LtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#lt}.
	 * @param ctx the parse tree
	 */
	void exitLt(PPParser.LtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#loe}.
	 * @param ctx the parse tree
	 */
	void enterLoe(PPParser.LoeContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#loe}.
	 * @param ctx the parse tree
	 */
	void exitLoe(PPParser.LoeContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#eq}.
	 * @param ctx the parse tree
	 */
	void enterEq(PPParser.EqContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#eq}.
	 * @param ctx the parse tree
	 */
	void exitEq(PPParser.EqContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#goe}.
	 * @param ctx the parse tree
	 */
	void enterGoe(PPParser.GoeContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#goe}.
	 * @param ctx the parse tree
	 */
	void exitGoe(PPParser.GoeContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#gt}.
	 * @param ctx the parse tree
	 */
	void enterGt(PPParser.GtContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#gt}.
	 * @param ctx the parse tree
	 */
	void exitGt(PPParser.GtContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#funCall}.
	 * @param ctx the parse tree
	 */
	void enterFunCall(PPParser.FunCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#funCall}.
	 * @param ctx the parse tree
	 */
	void exitFunCall(PPParser.FunCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#callee}.
	 * @param ctx the parse tree
	 */
	void enterCallee(PPParser.CalleeContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#callee}.
	 * @param ctx the parse tree
	 */
	void exitCallee(PPParser.CalleeContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#read}.
	 * @param ctx the parse tree
	 */
	void enterRead(PPParser.ReadContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#read}.
	 * @param ctx the parse tree
	 */
	void exitRead(PPParser.ReadContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#write}.
	 * @param ctx the parse tree
	 */
	void enterWrite(PPParser.WriteContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#write}.
	 * @param ctx the parse tree
	 */
	void exitWrite(PPParser.WriteContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#funcName}.
	 * @param ctx the parse tree
	 */
	void enterFuncName(PPParser.FuncNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#funcName}.
	 * @param ctx the parse tree
	 */
	void exitFuncName(PPParser.FuncNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#tabGet}.
	 * @param ctx the parse tree
	 */
	void enterTabGet(PPParser.TabGetContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#tabGet}.
	 * @param ctx the parse tree
	 */
	void exitTabGet(PPParser.TabGetContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#alloc}.
	 * @param ctx the parse tree
	 */
	void enterAlloc(PPParser.AllocContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#alloc}.
	 * @param ctx the parse tree
	 */
	void exitAlloc(PPParser.AllocContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#exprNum}.
	 * @param ctx the parse tree
	 */
	void enterExprNum(PPParser.ExprNumContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#exprNum}.
	 * @param ctx the parse tree
	 */
	void exitExprNum(PPParser.ExprNumContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#exprBool}.
	 * @param ctx the parse tree
	 */
	void enterExprBool(PPParser.ExprBoolContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#exprBool}.
	 * @param ctx the parse tree
	 */
	void exitExprBool(PPParser.ExprBoolContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(PPParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(PPParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#varName}.
	 * @param ctx the parse tree
	 */
	void enterVarName(PPParser.VarNameContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#varName}.
	 * @param ctx the parse tree
	 */
	void exitVarName(PPParser.VarNameContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#assignVar}.
	 * @param ctx the parse tree
	 */
	void enterAssignVar(PPParser.AssignVarContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#assignVar}.
	 * @param ctx the parse tree
	 */
	void exitAssignVar(PPParser.AssignVarContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#assignTab}.
	 * @param ctx the parse tree
	 */
	void enterAssignTab(PPParser.AssignTabContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#assignTab}.
	 * @param ctx the parse tree
	 */
	void exitAssignTab(PPParser.AssignTabContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#if}.
	 * @param ctx the parse tree
	 */
	void enterIf(PPParser.IfContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#if}.
	 * @param ctx the parse tree
	 */
	void exitIf(PPParser.IfContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#while}.
	 * @param ctx the parse tree
	 */
	void enterWhile(PPParser.WhileContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#while}.
	 * @param ctx the parse tree
	 */
	void exitWhile(PPParser.WhileContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#processCall}.
	 * @param ctx the parse tree
	 */
	void enterProcessCall(PPParser.ProcessCallContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#processCall}.
	 * @param ctx the parse tree
	 */
	void exitProcessCall(PPParser.ProcessCallContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#skipInstr}.
	 * @param ctx the parse tree
	 */
	void enterSkipInstr(PPParser.SkipInstrContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#skipInstr}.
	 * @param ctx the parse tree
	 */
	void exitSkipInstr(PPParser.SkipInstrContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#seq}.
	 * @param ctx the parse tree
	 */
	void enterSeq(PPParser.SeqContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#seq}.
	 * @param ctx the parse tree
	 */
	void exitSeq(PPParser.SeqContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#instr}.
	 * @param ctx the parse tree
	 */
	void enterInstr(PPParser.InstrContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#instr}.
	 * @param ctx the parse tree
	 */
	void exitInstr(PPParser.InstrContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#instru}.
	 * @param ctx the parse tree
	 */
	void enterInstru(PPParser.InstruContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#instru}.
	 * @param ctx the parse tree
	 */
	void exitInstru(PPParser.InstruContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(PPParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(PPParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#pair}.
	 * @param ctx the parse tree
	 */
	void enterPair(PPParser.PairContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#pair}.
	 * @param ctx the parse tree
	 */
	void exitPair(PPParser.PairContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#function}.
	 * @param ctx the parse tree
	 */
	void enterFunction(PPParser.FunctionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#function}.
	 * @param ctx the parse tree
	 */
	void exitFunction(PPParser.FunctionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PPParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(PPParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PPParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(PPParser.ProgramContext ctx);
}