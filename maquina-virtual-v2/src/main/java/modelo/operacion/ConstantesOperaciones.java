/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Enum.java to edit this template
 */
package modelo.operacion;

/**
 *
 * @author valen
 */
public class ConstantesOperaciones
{
    private static final String[] nombresOperaciones;
    private static final int cantOperaciones = 32;
    
    static 
    {
        nombresOperaciones = new String[cantOperaciones];
        nombresOperaciones[0x10] = "MOV";
        nombresOperaciones[0x11] = "ADD";
        nombresOperaciones[0x12] = "SUB";
        nombresOperaciones[0x13] = "MUL";
        nombresOperaciones[0x14] = "DIV";
        nombresOperaciones[0x15] = "CMP";
        nombresOperaciones[0x16] = "SHL";
        nombresOperaciones[0x17] = "SHR";
        nombresOperaciones[0x18] = "SAR";
        nombresOperaciones[0x19] = "AND";
        nombresOperaciones[0x1A] = "OR";
        nombresOperaciones[0x1B] = "XOR";
        nombresOperaciones[0x1C] = "SWAP";
        nombresOperaciones[0x1D] = "LDL";
        nombresOperaciones[0x1E] = "LDH";
        nombresOperaciones[0x1F] = "RND";
        nombresOperaciones[0x00] = "SYS";
        nombresOperaciones[0x01] = "JMP";
        nombresOperaciones[0x02] = "JZ";
        nombresOperaciones[0x03] = "JP";
        nombresOperaciones[0x04] = "JN";
        nombresOperaciones[0x05] = "JNZ";
        nombresOperaciones[0x06] = "JNP";
        nombresOperaciones[0x07] = "JNN";
        nombresOperaciones[0x08] = "NOT";
        nombresOperaciones[0x0B] = "PUSH";
        nombresOperaciones[0x0C] = "POP";
        nombresOperaciones[0x0D] = "CALL";
        nombresOperaciones[0x0E] = "RET";
        nombresOperaciones[0x0F] = "STOP";
    }
    
    public static String getNombre(int codOperacion)
    {
        return nombresOperaciones[codOperacion];
    }
}
