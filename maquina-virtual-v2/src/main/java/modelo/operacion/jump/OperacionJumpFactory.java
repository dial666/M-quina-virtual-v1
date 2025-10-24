/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.jump;

import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class OperacionJumpFactory
{
    public static OperacionJump creaOperacionJump(int codOP) throws VMException
    {
        OperacionJump op = switch (codOP)
        {
            case 0x01 -> new Jmp();
            case 0x02 -> new Jz();
            case 0x03 -> new Jp();
            case 0x04 -> new Jn();
            case 0x05 -> new Jnz();
            case 0x06 -> new Jnp();
            case 0x07 -> new Jnn();
            default -> throw new VMException("codigo de operacion desconocido");
        };
        return op;
    }
}
