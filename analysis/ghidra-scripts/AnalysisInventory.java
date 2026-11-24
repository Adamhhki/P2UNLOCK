import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;

public class AnalysisInventory extends GhidraScript {
    @Override
    public void run() throws Exception {
        Program p = getCurrentProgram();
        if (p == null) return;
        File out = new File("/workspaces/P2UNLOCK/.analysis-output/ghidra-inventory.txt");
        FileWriter w = new FileWriter(out, true);
        w.write("\nPROGRAM " + p.getName() + "\n");
        long count = 0;
        for (Function f : p.getFunctionManager().getFunctions(true)) {
            count++;
            w.write("FUNC " + f.getEntryPoint() + " " + f.getName() + " " + f.getBody().getNumAddresses() + "\n");
        }
        w.write("FUNCTION_COUNT " + count + "\n");
        w.write("SYMBOLS\n");
        SymbolTable symbols = p.getSymbolTable();
        for (Symbol s : symbols.getAllSymbols(true)) {
            if (s.isExternal()) {
                w.write("EXT " + s.getName() + " " + s.getAddress() + "\n");
            }
        }
        w.close();
    }
}
