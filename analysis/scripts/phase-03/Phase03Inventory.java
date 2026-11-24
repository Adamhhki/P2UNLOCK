import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.mem.*;
import java.io.*;
import java.util.*;

public class Phase03Inventory extends GhidraScript {
    private String esc(String s) {
        if (s == null) return "";
        return s.replace(",", " ").replace("\n", " ").replace("\r", " ");
    }
    @Override
    public void run() throws Exception {
        Program p = getCurrentProgram();
        if (p == null) return;
        File dir = new File("/workspaces/P2UNLOCK/.analysis-output/phase03");
        dir.mkdirs();
        FileWriter functions = new FileWriter(new File(dir, p.getName() + "-functions.csv"));
        functions.write("address,entry,rva,name,body_size,incoming,outgoing\n");
        for (Function f : p.getFunctionManager().getFunctions(true)) {
            long rva = f.getEntryPoint().getOffset();
            int incoming = 0;
            ReferenceIterator incomingIt = p.getReferenceManager().getReferencesTo(f.getEntryPoint());
            while (incomingIt.hasNext()) { incomingIt.next(); incoming++; }
            int outgoing = 0;
            AddressSetView body = f.getBody();
            AddressIterator addresses = body.getAddresses(true);
            while (addresses.hasNext()) {
                Address a = addresses.next();
                Reference[] outgoingRefs = p.getReferenceManager().getReferencesFrom(a);
                outgoing += outgoingRefs.length;
            }
            functions.write(esc(f.getEntryPoint().toString())+","+esc(f.getEntryPoint().toString())+","+
                Long.toString(rva)+","+esc(f.getName())+","+f.getBody().getNumAddresses()+","+incoming+","+outgoing+"\n");
        }
        functions.close();

        FileWriter api = new FileWriter(new File(dir, p.getName() + "-external-api-xrefs.csv"));
        api.write("api,address,to_address,from_function\n");
        SymbolTable st = p.getSymbolTable();
        for (Symbol s : st.getAllSymbols(true)) {
            if (!s.isExternal()) continue;
            String apiName = s.getName();
            ReferenceIterator it = p.getReferenceManager().getReferencesTo(s.getAddress());
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = p.getFunctionManager().getFunctionContaining(r.getFromAddress());
                api.write(esc(apiName)+","+esc(r.getFromAddress().toString())+","+esc(s.getAddress().toString())+","+
                    esc(f == null ? "UNKNOWN" : f.getName())+"\n");
            }
        }
        api.close();

        FileWriter strings = new FileWriter(new File(dir, p.getName() + "-string-xrefs.csv"));
        strings.write("string,address,xref_address,in_function\n");
        Listing listing = p.getListing();
        DataIterator di = listing.getData(true);
        while (di.hasNext()) {
            Data d = di.next();
            if (d.hasStringValue()) {
                String text = d.getValue().toString();
                if (text.length() < 3) continue;
                ReferenceIterator it = p.getReferenceManager().getReferencesTo(d.getAddress());
                while (it.hasNext()) {
                    Reference r = it.next();
                    Function f = p.getFunctionManager().getFunctionContaining(r.getFromAddress());
                    strings.write("\""+esc(text)+"\",\""+esc(d.getAddress().toString())+"\",\""+
                        esc(r.getFromAddress().toString())+"\",\""+esc(f == null ? "UNKNOWN" : f.getName())+"\"\n");
                }
            }
        }
        strings.close();
    }
}
