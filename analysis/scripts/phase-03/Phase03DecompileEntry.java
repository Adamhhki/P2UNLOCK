import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;

public class Phase03DecompileEntry extends GhidraScript {
    @Override
    public void run() throws Exception {
        Program p = getCurrentProgram();
        if (p == null) return;
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(p);
        File dir = new File("/workspaces/P2UNLOCK/.analysis-output/phase03");
        dir.mkdirs();
        FileWriter w = new FileWriter(new File(dir, p.getName()+"-entry-decompile.txt"));
        Address entry = p.getAddressFactory().getDefaultAddressSpace().getAddress(p.getImageBase().getOffset()+0x4d120);
        Function f = p.getFunctionManager().getFunctionAt(entry);
        if (f == null) f = p.getFunctionManager().getFunctionContaining(entry);
        w.write("ADDRESS "+entry+"\n");
        w.write("FUNCTION "+(f == null ? "UNKNOWN" : f.getName()+" "+f.getEntryPoint())+"\n");
        if (f != null) {
            DecompileResults r = decomp.decompileFunction(f, 60, monitor);
            w.write(r.getDecompiledFunction() == null ? "DECOMP_FAILED "+r.getErrorMessage() :
                r.getDecompiledFunction().getC());
        }
        w.close();
        decomp.dispose();
    }
}
