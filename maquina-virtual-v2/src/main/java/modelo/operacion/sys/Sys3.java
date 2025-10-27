/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.sys;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author Matu
 */
public class Sys3 implements IOperacion{

    public Sys3() {
    }

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int dirLogica = new OperandoRegistroE(ConstantesRegistros.EDX.getCodigo()).getValor(mv);
        int maxCant = new OperandoRegistroE(ConstantesRegistros.ECX.getCodigo()).getValor(mv);
        
        if (maxCant < 0 )
            throw new VMException("el largo de la cadena no puede ser menor a 0");
                
        System.out.printf(" [%04X]: ", mv.getPreviewDirFisica(dirLogica));
        String cadena = mv.getScanner().nextLine();
        
        for (int i = 0; (i < maxCant || maxCant==-1) && i < cadena.length(); i++)
        {
            mv.setValorMemoriaModifReg(dirLogica, 1, cadena.charAt(i));
            dirLogica += 1;
        }
        mv.setValorMemoriaModifReg(dirLogica, 1, 0x00);
    }
    
}
