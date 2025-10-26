/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import modelo.excepciones.SegmentationFaultException;
import modelo.excepciones.VMException;
import modelo.operacion.sys.parser.INumberToStringParser;
import modelo.operacion.sys.parser.NmbToStrCaracter;
import modelo.operacion.sys.parser.NmbToStrHexadecimal;
import modelo.operacion.sys.parser.NmbToStringCaracterMuestra0;
import modelo.operando.Operando;
import modelo.operando.OperandoInmediato;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistro;
import modelo.utils.IntUtils;
import modelo.utils.StringUtils;

/**
 *
 * @author valen
 */
public class MaquinaVirtual implements UnidadIO, IMaquinaVirtual, IDebuggeable
{
    private Memoria memoria;
    private Registros registros;
    private TablaSegmentos tablaSegmentos;
    private boolean disassembler;
    private boolean pasoAPaso;
    private boolean atenderDebugger;
    private boolean breakpoint;
    private CreadorVMI creadorVMI;
    private Scanner scanner;
    
    public MaquinaVirtual(Memoria memoria, Registros registros, TablaSegmentos tablaSegmentos, boolean disassembler, CreadorVMI creadorVMI)
    {
        this.memoria = memoria;
        this.registros = registros;
        this.tablaSegmentos = tablaSegmentos;
        this.disassembler = disassembler;
        this.creadorVMI = creadorVMI;
        this.atenderDebugger = creadorVMI.getArchVmi() != null;
        this.pasoAPaso = this.breakpoint = false;
        this.scanner = new Scanner(System.in);
    }

    @Override
    public int getValor(Operando operando) throws SegmentationFaultException
    {
        throw new IllegalArgumentException("operando desconocido");
    }

    @Override
    public int getValor(OperandoInmediato operando)
    {
        return operando.getValor();
    }
    
    @Override
    public int getValor(OperandoRegistro operando)
    {
        return this.registros.getValor(operando);
    }
    
    @Override
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
    
    @Override
    public void setValor(OperandoInmediato operando, int valor)
    {
        throw new IllegalArgumentException("no se puede colocar un valor a un inmediato");
    }
    
    @Override
    public void setValor(OperandoRegistro operando, int valor)
    {
        this.registros.setValor(operando, valor);
    }
    
    @Override
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
    public void ejecutar() throws VMException, IOException
    {
        Instruccion instruccion;
        Debugger debugger = new Debugger();
        if (this.disassembler == true)
        {
            mostrarKS();
            System.out.print(">");
        }
  
        while (registros.getIP() != -1)
        {          
            instruccion = leerInstruccion();
            instruccion.ejecutar(this);
            
            if (this.breakpoint == true || this.pasoAPaso == true)
                debugger.ejecutar(this);
        }
    }
    
    @Override
    public void creaImagen() throws VMException, FileNotFoundException, IOException
    {
        this.creadorVMI.creaImagen(this.memoria.getBytes(), this.registros.getBytes(), this.tablaSegmentos.getBytes());
    }
    
    protected Instruccion leerInstruccion() throws SegmentationFaultException, VMException
    {
        int dirFisica;
        try
        {
            dirFisica = getPreviewDirFisica(registros.getIP());
        } catch (SegmentationFaultException e)
        {
            throw new VMException("");
        }
        int ins = getValorMemoria(registros.getIP(), 1);
        int tipo1 = (ins >> 6) & 0b11;
        int tipo2 = (ins >> 4) & 0b11;
        registros.setOPC(ins & 0x1F);
        registros.setOP1(getValorMemoria(registros.getIP()+1, tipo1));
        registros.setOP2(getValorMemoria(registros.getIP()+1+tipo1, tipo2));
        registros.setOP1((registros.getOP1() & 0x00FFFFFF) | (tipo1 << 24));
        registros.setOP2((registros.getOP2() & 0x00FFFFFF) | (tipo2 << 24));
        registros.setIP(registros.getIP() + 1 + tipo1 + tipo2);
        
        if (tipo2 != 0)
        {
            int temp = registros.getOP1();
            int temp2 = tipo1;
            registros.setOP1(registros.getOP2());
            registros.setOP2(temp);
            tipo1 = tipo2;
            tipo2 = temp2;
        }
        
        Instruccion instruccion = new Instruccion(registros.getOPC(), registros.getOP1(), registros.getOP2());
        
        if (this.disassembler == true)
        {
            String hexa = IntUtils.getHexFormat(1, ins) + IntUtils.getHexFormat(tipo2, registros.getOP2()) + IntUtils.getHexFormat(tipo1, registros.getOP1());
            hexa += StringUtils.getEspacios(22, hexa);
            System.out.printf("[%04X]:%s| %s %n", dirFisica, hexa, instruccion);
        }
        
        return instruccion;
    }

    @Override
    public int getPreviewDirFisica(int dirLogica) throws SegmentationFaultException
    {
        return this.tablaSegmentos.getDirFisica(dirLogica, 1);
    }

    @Override
    public boolean isPasoAPaso()
    {
        return this.pasoAPaso;
    }

    @Override
    public boolean isAtenderDebugger()
    {
        return this.atenderDebugger;
    }

    @Override
    public void setPasoAPaso(boolean pasoAPaso)
    {
        this.pasoAPaso = pasoAPaso;
    }

    @Override
    public void setBreakpoint(boolean breakpoint)
    {
        this.breakpoint = breakpoint;
    }


    @Override
    public Scanner getScanner()
    {
        return scanner;
    }
    
    protected void mostrarKS()
    {
        int dirFisica;
        int i;
        int dirLogica = registros.getKS();
        int leido;
        INumberToStringParser parserCar = new NmbToStringCaracterMuestra0();
        String hexa;
        String cadena;
        try
        {
            while (true)
            {
                dirFisica = getPreviewDirFisica(dirLogica);
                i = 0;
                cadena = hexa = "";
                do
                {                    
                 leido = getValorMemoria(dirLogica, 1);  
                 if (i < 6)
                 {
                     hexa += IntUtils.getHexFormat(1, leido);
                     i++;
                 }
                 cadena += parserCar.numberToString(leido, 1);
                 dirLogica++;
                } while (leido != 0);
                 
                if (i == 6)
                    hexa += " ..";
                hexa += StringUtils.getEspacios(22, hexa);
                System.out.printf("[%04X]:%s| \"%s\" %n", dirFisica, hexa, cadena);
            }
        } 
        catch (SegmentationFaultException e)
        {
        }
    }
}
