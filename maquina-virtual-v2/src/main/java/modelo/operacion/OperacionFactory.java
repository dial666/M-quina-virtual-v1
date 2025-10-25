/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion;

import modelo.excepciones.VMException;
import modelo.operacion.jump.OperacionJumpFactory;
import modelo.operacion.load.Ldh;
import modelo.operacion.load.Ldl;
import modelo.operacion.operacionbinaria.OperacionBinariaFactory;
import modelo.operacion.sys.OperacionSys;

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
            else
                op = switch (codOP)
                {
                    case 0x10 -> new Mov();
                    case 0x1C -> new Swap();
                    case 0x1D -> new Ldl();
                    case 0x1E -> new Ldh();
                    case 0x1F -> new Rnd();
                    case 0x08 -> new Not();
                    case 0x0F -> new Stop();
                    case 0x00 -> new OperacionSys();
                    default -> throw new VMException("codigo de operacion desconocido");
                };
        
        return op;
    }
}
