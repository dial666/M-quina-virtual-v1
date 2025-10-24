/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package prueba;

import java.rmi.dgc.VMID;
import modelo.IMaquinaVirtual;
import modelo.MaquinaVirtual;
import modelo.Memoria;
import modelo.Registros;
import modelo.UnidadIO;
import modelo.inicio.MVFactory;
import modelo.operando.Operando;
import modelo.operando.OperandoFactory;
import modelo.operando.OperandoRegistro;
import modelo.operando.OperandoRegistroE;
import modelo.operando.OperandoRegistroH;
import modelo.operando.OperandoRegistroL;
import modelo.operando.OperandoRegistroX;

/**
 *
 * @author valen
 */
public class MaquinaVirtualV2 {

    public static void main(String[] args) {
        MVFactory mvf = new MVFactory();
        OperandoFactory of = new OperandoFactory();
        try
        {
           IMaquinaVirtual mv = mvf.creaMV(args);
           
           mv.ejecutar();
          
           
           mv.creaImagen();
            
        } 
        catch (Exception e)
        {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
}
