/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.IOException;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.VMException;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistro;
import modelo.utils.IntUtils;

/**
 *
 * @author valen
 */
public class MaquinaVirtual implements UnidadIO, IMaquinaVirtual
{
    private Memoria memoria;
    private Registros registros;
    private TablaSegmentos tablaSegmentos;
    private boolean disassembler;
    private CreadorVMI creadorVMI;
    
    public MaquinaVirtual(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos, boolean disassembler, CreadorVMI creadorVMI)
    {
        this.memoria = memoria;
        this.registros = registros;
        this.tablaSegmentos = tablaSegmentos;
        this.disassembler = disassembler;
        this.creadorVMI = creadorVMI;
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
        int dirLogica = getValor(operando.getOperandoRegistro()) + operando.getOffset();
        int cantBytes = 4 - operando.getCodTamanioCelda();
        return getValorMemoriaModificaReg(dirLogica, cantBytes);
    }
    
    @Override
    public int getValorMemoriaModificaReg(int dirLogica, int cantBytes) throws SegmentationFaultException
    {
        this.registros.setLAR(dirLogica);
        int dirFisica = this.tablaSegmentos.getDirFisica(dirLogica, cantBytes);
        int valorMar = IntUtils.putHigh(0, cantBytes);
        valorMar = IntUtils.putLow(valorMar, dirFisica);
        this.registros.setMAR(valorMar);
        this.registros.setMBR(this.memoria.getValor(dirFisica, cantBytes));
        return this.registros.getMBR();
    }
    
    public int getValorMemoria(int dirLogica, int cantBytes) throws SegmentationFaultException
    {
        int dirFisica = this.tablaSegmentos.getDirFisica(dirLogica, cantBytes);
        return this.memoria.getValor(dirFisica, cantBytes);
    }
    
    @Override
    public void setValor(Operando operando, int valor) throws SegmentationFaultException
    {
        operando.setValor(this, valor);
    }
    
    public void setValor(OperandoInmediato operando, int valor)
    {
        throw new IllegalArgumentException("no se puede colocar un valor a un inmediato");
    }
    
    public void setValor(OperandoRegistro operando, int valor)
    {
        this.registros.setValor(operando, valor);
    }
    
    public void setValor(OperandoMemoria operando, int valor) throws SegmentationFaultException
    {
        int dirLogica = getValor(operando.getOperandoRegistro()) + operando.getOffset();
        int cantBytes = 4 - operando.getCodTamanioCelda();
        setValorMemoriaModifReg(dirLogica, cantBytes, valor);
    }
    
    @Override
    public void setValorMemoriaModifReg(int dirLogica, int cantBytes, int valor) throws SegmentationFaultException
    {
        this.registros.setLAR(dirLogica);
        int dirFisica = this.tablaSegmentos.getDirFisica(dirLogica, cantBytes);
        int valorMar = IntUtils.putHigh(0, cantBytes);
        valorMar = IntUtils.putLow(valorMar, dirFisica);
        this.registros.setMAR(valorMar);
        this.registros.setMBR(valor);
        this.memoria.setValor(dirFisica, cantBytes, valor);
    }

    @Override
    public void ejecutar() throws VMException
    {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }
    
    @Override
    public void creaImagen() throws VMException, FileNotFoundException, IOException
    {
        this.creadorVMI.creaImagen(this.memoria.getBytes(), this.registros.getBytes(), this.tablaSegmentos.getBytes());
    }
}
