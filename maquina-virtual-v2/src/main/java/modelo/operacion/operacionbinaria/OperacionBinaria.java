/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.operacionbinaria;

import javax.tools.OptionChecker;
import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operacion.OperacionFlag;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public abstract class OperacionBinaria implements IOperacion
{
    Operando opCC;
    
    public OperacionBinaria()
    {
        this.opCC = new OperandoRegistroE(ConstantesRegistros.CC.getCodigo());
    }
    
    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
        int valorA = opA.getValor(mv);
        int valorB = opB.getValor(mv);
        int resultado = cuenta(valorA, valorB);
        
        IOperacion setFlag = new OperacionFlag();
        setFlag.ejecutar(opCC, new OperandoInmediato(resultado), mv);
        
        setAC(valorA, valorB, mv);
        setValor(opA, resultado, mv);      
    }
    
    public abstract int cuenta(int valorA, int valorB);
    
    public void setValor(Operando opA, int resultado, UnidadIO mv) throws VMException
    {
        opA.setValor(mv, resultado);
    }
    
    public void setAC(int valorA, int valorB, UnidadIO mv)
    {
        
    }
}
