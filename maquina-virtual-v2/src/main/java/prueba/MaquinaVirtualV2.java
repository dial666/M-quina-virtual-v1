/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package prueba;

import modelo.IMaquinaVirtual;
import modelo.inicio.MVFactory;

/**
 *
 * @author valen
 */
public class MaquinaVirtualV2 {

    public static void main(String[] args) {
        MVFactory mvf = new MVFactory();
        try
        {
           IMaquinaVirtual mv = mvf.creaMV(args);
           
           mv.ejecutar();
            //System.out.println(IntUtils.getHexFormat(3, 0x00000004));
        } 
        catch (Exception e)
        {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
}
