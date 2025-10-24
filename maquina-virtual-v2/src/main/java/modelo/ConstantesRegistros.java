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
    OP2(6),
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
    
    private static final int[] SHIFT = {0, 0, 8, 0};
    private static final int[] MASK  = {0xFFFFFFFF, 0x000000FF, 0x0000FF00, 0x0000FFFF};
    private static final String[] NOMBRESREGISTROS;
    private static final int CANTREGISTROS = 32;
    private final int codigo;
        
    static 
    {
        NOMBRESREGISTROS = new String[ConstantesRegistros.CANTREGISTROS];
        NOMBRESREGISTROS[LAR.getCodigo()] = "LAR";
        NOMBRESREGISTROS[MAR.getCodigo()] = "MAR";
        NOMBRESREGISTROS[MBR.getCodigo()] = "MBR";
        NOMBRESREGISTROS[IP.getCodigo()] = "IP";
        NOMBRESREGISTROS[OPC.getCodigo()] = "OPC";
        NOMBRESREGISTROS[OP1.getCodigo()] = "OP1";
        NOMBRESREGISTROS[OP2.getCodigo()] = "OP2";
        NOMBRESREGISTROS[SP.getCodigo()] = "SP";
        NOMBRESREGISTROS[BP.getCodigo()] = "BP";
        NOMBRESREGISTROS[EAX.getCodigo()] = "EAX";
        NOMBRESREGISTROS[EBX.getCodigo()] = "EBX";
        NOMBRESREGISTROS[ECX.getCodigo()] = "ECX";
        NOMBRESREGISTROS[EDX.getCodigo()] = "EDX";
        NOMBRESREGISTROS[EEX.getCodigo()] = "EEX";
        NOMBRESREGISTROS[EFX.getCodigo()] = "EFX";
        NOMBRESREGISTROS[AC.getCodigo()] = "AC";
        NOMBRESREGISTROS[CC.getCodigo()] = "CC";
        NOMBRESREGISTROS[CS.getCodigo()] = "CS";
        NOMBRESREGISTROS[DS.getCodigo()] = "DS";
        NOMBRESREGISTROS[ES.getCodigo()] = "ES";
        NOMBRESREGISTROS[SS.getCodigo()] = "SS";
        NOMBRESREGISTROS[KS.getCodigo()] = "KS";
        NOMBRESREGISTROS[PS.getCodigo()] = "PS";
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
        return NOMBRESREGISTROS[codigo];
    }

    public static int getCantidadRegistros()
    {
        return CANTREGISTROS;
    }
    
    public static int getMask(int codSector)
    {
        return MASK[codSector];
    }
}
