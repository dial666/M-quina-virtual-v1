/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package prueba;

import modelo.Memoria;
import modelo.Registros;
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
        OperandoFactory of = new OperandoFactory();
        Registros r = new Registros();
        Memoria m = new Memoria(100);
        try
        {
           Operando opm = of.creaOperando(3, 0xC70008);
            Operando opr = of.creaOperando(1, 0x07);
            Operando opi = of.creaOperando(2, 0xFFFFFFF4);
            System.out.println(opm);
            System.out.println(opr);
            System.out.println(opi); 
            
            OperandoRegistro opr2 = new OperandoRegistroH(26);
            OperandoRegistro opr3 = new OperandoRegistroE(26);
            r.setValor(opr2, -2);
            r.setValor(opr3, 0);
            System.out.printf("0x%08X%n", r.getValor(opr3)); 
            
            m.setValor(0, 2, 5);
            System.out.printf("0x%08X%n", m.getValor(0, 4)); 
        } 
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }
    }
}
