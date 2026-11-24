import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;

public class Phase03DecompileSelected extends GhidraScript {
    @Override
    public void run() throws Exception {
        Program p = getCurrentProgram();
        if (p == null) return;
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(p);
        File dir = new File("/workspaces/P2UNLOCK/.analysis-output/phase03/decompile");
        dir.mkdirs();
        String[] names = {
            "140044680","14000ed70","140011210","140012c60","140008fe0","14000bb40",
            "14001ab30","14001b290","1400299b0","14002ba00","14003a820","14002e150"
        };
        for (String hex : names) {
            Address a = p.getAddressFactory().getDefaultAddressSpace().getAddress(hex);
            Function f = p.getFunctionManager().getFunctionAt(a);
            if (f == null) f = p.getFunctionManager().getFunctionContaining(a);
            if (f == null) continue;
            DecompileResults r = decomp.decompileFunction(f, 90, monitor);
            FileWriter w = new FileWriter(new File(dir, f.getEntryPoint()+"-"+f.getName()+".txt"));
            w.write("ADDRESS "+f.getEntryPoint()+"\nFUNCTION "+f.getName()+"\nSIZE "+f.getBody().getNumAddresses()+"\n");
            w.write(r.getDecompiledFunction() == null ? "DECOMP_FAILED "+r.getErrorMessage() : r.getDecompiledFunction().getC());
            w.close();
        }
        decomp.dispose();
    }
}
