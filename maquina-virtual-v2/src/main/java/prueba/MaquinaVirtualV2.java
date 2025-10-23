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
            UnidadIO mv = (MaquinaVirtual) (mvf.creaMV(args));
           
           Operando op1 = of.creaOperando(3, 0xDB0004);
           Operando op2 = of.creaOperando(2, 0x0002);
           
           op1.setValor(mv, op2.getValor(mv));
           
           Operando op3 = of.creaOperando(1, 0x8A);
          
           op3.setValor(mv, op1.getValor(mv));
           
           Operando op4 = of.creaOperando(3, 0x1B0000);
           
           op4.setValor(mv, op3.getValor(mv));
           
           mv.creaImagen();
            
        } 
        catch (Exception e)
        {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
}
