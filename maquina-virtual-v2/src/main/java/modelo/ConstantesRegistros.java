/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Enum.java to edit this template
 */
package modelo;

/**
 *
 * @author valen
 */
public enum ConstantesRegistros
{
    LAR(0),
    MAR(1),
    MBR(2),
    IP(3),
    OPC(4),
    OP1(5),
    OP2(5),
    SP(7),
    BP(8),
    EAX(10),
    EBX(11),
    ECX(12),
    EDX(13),
    EEX(14),
    EFX(15),
    AC(16),
    CC(17),
    CS(26),
    DS(27),
    ES(28),
    SS(29),
    KS(30),
    PS(31);
    
    private static final String[] nombresRegistros;
    private static final int cantidadRegistros = 32;
    private final int codigo;
        
    static 
    {
        nombresRegistros = new String[ConstantesRegistros.cantidadRegistros];
        nombresRegistros[LAR.getCodigo()] = "LAR";
        nombresRegistros[MAR.getCodigo()] = "MAR";
        nombresRegistros[MBR.getCodigo()] = "MBR";
        nombresRegistros[IP.getCodigo()] = "IP";
        nombresRegistros[OPC.getCodigo()] = "OPC";
        nombresRegistros[OP1.getCodigo()] = "OP1";
        nombresRegistros[OP2.getCodigo()] = "OP2";
        nombresRegistros[SP.getCodigo()] = "SP";
        nombresRegistros[BP.getCodigo()] = "BP";
        nombresRegistros[EAX.getCodigo()] = "EAX";
        nombresRegistros[EBX.getCodigo()] = "EBX";
        nombresRegistros[ECX.getCodigo()] = "ECX";
        nombresRegistros[EDX.getCodigo()] = "EDX";
        nombresRegistros[EEX.getCodigo()] = "EEX";
        nombresRegistros[EFX.getCodigo()] = "EFX";
        nombresRegistros[AC.getCodigo()] = "AC";
        nombresRegistros[CC.getCodigo()] = "CC";
        nombresRegistros[CS.getCodigo()] = "CS";
        nombresRegistros[DS.getCodigo()] = "DS";
        nombresRegistros[ES.getCodigo()] = "ES";
        nombresRegistros[SS.getCodigo()] = "SS";
        nombresRegistros[KS.getCodigo()] = "KS";
        nombresRegistros[PS.getCodigo()] = "PS";
    }
    
    private ConstantesRegistros(int codigo)
    {
        this.codigo = codigo;
    }

    public int getCodigo()
    {
        return codigo;
    }  
    
    public static String getNombre(int codigo)
    {
        return nombresRegistros[codigo];
    }
}
