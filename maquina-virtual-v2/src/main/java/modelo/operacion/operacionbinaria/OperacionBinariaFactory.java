/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.operacionbinaria;

import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class OperacionBinariaFactory
{
    public static OperacionBinaria creaOperacionBinaria(int codOp) throws VMException
    {
        OperacionBinaria op = switch (codOp)
        {
            case 0x11 -> new Add();
            case 0x12 -> new Sub();
            case 0x13 -> new Mul();
            case 0x14 -> new Div();
            case 0x15 -> new Cmp();
            case 0x16 -> new Shl();
            case 0x17 -> new Shr();
            case 0x18 -> new Sar();
            case 0x19 -> new And();
            case 0x1A -> new Or();
            case 0x1B -> new Xor();
            default -> throw new VMException("codigo de operacion desconocido");
        };
        return op;
    }
}
