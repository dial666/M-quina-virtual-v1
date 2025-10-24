/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.excepciones.VMException;
import modelo.operacion.jump.OperacionJumpFactory;
import modelo.operacion.operacionbinaria.OperacionBinariaFactory;

/**
 *
 * @author valen
 */
public class OperacionFactory
{
    
    public static IOperacion creaOperacion(int codOP) throws VMException
    {
        IOperacion op = null;
        if (codOP >= 0x11 && codOP <= 0x1B)
            op = OperacionBinariaFactory.creaOperacionBinaria(codOP);
        else
            if (codOP >= 0x01 && codOP <= 0x07)
                op =  OperacionJumpFactory.creaOperacionJump(codOP);
        
        return op;
    }
}
