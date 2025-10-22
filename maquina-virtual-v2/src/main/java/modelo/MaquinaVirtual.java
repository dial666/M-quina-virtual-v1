/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import modelo.excepciones.SegmentationFaultException;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistro;

/**
 *
 * @author valen
 */
public class MaquinaVirtual implements Contexto
{
    private Memoria memoria;
    private Registros registros;
    private TablaSegmentos tablaSegmentos;
    
    public MaquinaVirtual(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos)
    {
        this.memoria = memoria;
        this.registros = registros;
        this.tablaSegmentos = tablaSegmentos;
    }

    @Override
    public int getValor(Operando operando) throws SegmentationFaultException
    {
        return operando.getValor(this);
    }

    public int getValor(OperandoInmediato operando)
    {
        return operando.getValor();
    }
    
    public int getValor(OperandoRegistro operando)
    {
        return this.registros.getValor(operando);
    }
    
    public int getValor(OperandoMemoria operando) throws SegmentationFaultException
    {
        return 0;
    }
    
    @Override
    public void setValor(Operando operando) throws SegmentationFaultException, IllegalArgumentException
    {
        operando.setValor(this);
    }
}
