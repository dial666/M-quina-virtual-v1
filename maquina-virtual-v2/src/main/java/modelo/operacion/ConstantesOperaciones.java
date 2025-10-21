/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Enum.java to edit this template
 */
package modelo.operacion;

/**
 *
 * @author valen
 */
public enum ConstantesOperaciones
{
    MOV(0x10),
    ADD(0x11),
    SUB(0x12),
    MUL(0x13),
    DIV(0x14),
    CMP(0x15),
    SHL(0x16),
    SHR(0x17),
    SAR(0x18),
    AND(0x19),
    OR(0x1A),
    XOR(0x1B),
    SWAP(0x1C),
    LDL(0x1D),
    LDH(0x1E),
    RND(0x1F),

    SYS(0x00),
    JMP(0x01),
    JZ(0x02),
    JP(0x03),
    JN(0x04),
    JNZ(0x05),
    JNP(0x06),
    JNN(0x07),
    NOT(0x08),
    PUSH(0x0B),
    POP(0x0C),
    CALL(0x0D),
    RET(0x0E),
    STOP(0x0F);
    private static final String[] nombresOperaciones;
    private static final int cantOperaciones = 32;
    private final int codigo;
    
    ConstantesOperaciones(int codOperacion)
    {
        this.codigo = codOperacion;
    }
    
    static 
    {
        nombresOperaciones = new String[cantOperaciones];
        nombresOperaciones[MOV.getCodigo()] = "MOV";
        nombresOperaciones[ADD.getCodigo()] = "ADD";
        nombresOperaciones[SUB.getCodigo()] = "SUB";
        nombresOperaciones[MUL.getCodigo()] = "MUL";
        nombresOperaciones[DIV.getCodigo()] = "DIV";
        nombresOperaciones[CMP.getCodigo()] = "CMP";
        nombresOperaciones[SHL.getCodigo()] = "SHL";
        nombresOperaciones[SHR.getCodigo()] = "SHR";
        nombresOperaciones[SAR.getCodigo()] = "SAR";
        nombresOperaciones[AND.getCodigo()] = "AND";
        nombresOperaciones[OR.getCodigo()] = "OR";
        nombresOperaciones[XOR.getCodigo()] = "XOR";
        nombresOperaciones[SWAP.getCodigo()] = "SWAP";
        nombresOperaciones[LDL.getCodigo()] = "LDL";
        nombresOperaciones[LDH.getCodigo()] = "LDH";
        nombresOperaciones[RND.getCodigo()] = "RND";
        nombresOperaciones[SYS.getCodigo()] = "SYS";
        nombresOperaciones[JMP.getCodigo()] = "JMP";
        nombresOperaciones[JZ.getCodigo()] = "JZ";
        nombresOperaciones[JP.getCodigo()] = "JP";
        nombresOperaciones[JN.getCodigo()] = "JN";
        nombresOperaciones[JNZ.getCodigo()] = "JNZ";
        nombresOperaciones[JNP.getCodigo()] = "JNP";
        nombresOperaciones[JNN.getCodigo()] = "JNN";
        nombresOperaciones[NOT.getCodigo()] = "NOT";
        nombresOperaciones[PUSH.getCodigo()] = "PUSH";
        nombresOperaciones[POP.getCodigo()] = "POP";
        nombresOperaciones[CALL.getCodigo()] = "CALL";
        nombresOperaciones[RET.getCodigo()] = "RET";
        nombresOperaciones[STOP.getCodigo()] = "STOP";
    }

    public int getCodigo()
    {
        return codigo;
    }
    
    public static String getNombre(ConstantesOperaciones op)
    {
        return nombresOperaciones[op.getCodigo()];
    }
    
    public static ConstantesOperaciones getTipoOperacion(int codigo) {
    for (ConstantesOperaciones op : ConstantesOperaciones.values()) {
        if (op.getCodigo() == codigo) {
            return op;
        }
    }
    return null;
}
}
