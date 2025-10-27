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
public class Sys4 implements IOperacion{

    public Sys4() {
    }

    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException {
        int dirLogica = new OperandoRegistroE(ConstantesRegistros.EDX.getCodigo()).getValor(mv);
                
        System.out.printf(" [%04X]: ", mv.getPreviewDirFisica(dirLogica));
        int valor;
        do  {
            valor = mv.getValorMemoriaModificaReg(dirLogica, 1);
            dirLogica += 1;
            System.out.print((char) valor);
        }
        while (valor != 0);
        System.out.println();
    }
    
}
