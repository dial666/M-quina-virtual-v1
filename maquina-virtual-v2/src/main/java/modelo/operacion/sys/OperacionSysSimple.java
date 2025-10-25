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
import modelo.operando.OperandoRegistroH;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public abstract class OperacionSysSimple implements IOperacion
{
    
    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int dirLogica = new OperandoRegistroE(ConstantesRegistros.EDX.getCodigo()).getValor(mv);
        int valorOpECX = new OperandoRegistroE(ConstantesRegistros.ECX.getCodigo()).getValor(mv);
        int modo = new OperandoRegistroE(ConstantesRegistros.EAX.getCodigo()).getValor(mv);
        int cantCeldas = IntUtils.getLowUnsigned(valorOpECX);
        int tamCelda = IntUtils.getHighUnsigned(valorOpECX);
        Operando opMAR = new OperandoRegistroE(ConstantesRegistros.MAR.getCodigo());
        
        if (tamCelda > 4 || tamCelda < 0 )
            throw new VMException("el tamanio de celda de memoria es invalido");
        
        setParser(modo);
        for (int i = 0; i < cantCeldas; i++)
        {
            System.out.printf("[%04X]: ", mv.getPreviewDirFisica(dirLogica));
            manipularMem(dirLogica, tamCelda, mv);
            dirLogica += tamCelda;
        }
    }
    
    public abstract void setParser(int modo) throws VMException;
    public abstract void manipularMem(int dirLogica, int tamCelda, UnidadIO mv) throws VMException;
}
