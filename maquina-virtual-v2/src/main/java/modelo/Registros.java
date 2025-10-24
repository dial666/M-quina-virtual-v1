/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;


import java.nio.ByteBuffer;
import modelo.operando.OperandoRegistro;

/**
 *
 * @author valen
 */
public class Registros
{ 
    private int[] registros;

    public Registros()
    {
        registros = new int[ConstantesRegistros.getCantidadRegistros()];
    }
    
    public int getValor(OperandoRegistro operando)
    {
        int valor = (this.registros[operando.getCodRegistro()] << operando.getShiftExtensionSigno()) >> operando.getShiftExtensionSigno();
        valor >>= operando.getShift();
        return valor;
    }
    
    public void setValor(OperandoRegistro operando, int valor)
    {
        valor &= operando.getMask();
        valor <<= operando.getShift();
        this.registros[operando.getCodRegistro()] &= operando.getMaskInicializa();
        this.registros[operando.getCodRegistro()] |= valor;
    }
    
    public void setLAR(int valor)
    {
        this.registros[ConstantesRegistros.LAR.getCodigo()] = valor;
    }
    
    public void setMAR(int valor)
    {
        this.registros[ConstantesRegistros.MAR.getCodigo()] = valor;
    }
    
    public void setMBR(int valor)
    {
        this.registros[ConstantesRegistros.MBR.getCodigo()] = valor;
    }
    
    public void setCS(int valor)
    {
        this.registros[ConstantesRegistros.CS.getCodigo()] = valor;
    }
    
    public void setDS(int valor)
    {
        this.registros[ConstantesRegistros.DS.getCodigo()] = valor;
    }
    
    public void setIP(int valor)
    {
        this.registros[ConstantesRegistros.IP.getCodigo()] = valor;
    }
    
    public void setKS(int valor)
    {
        this.registros[ConstantesRegistros.KS.getCodigo()] = valor;
    }
    
    public void setPS(int valor)
    {
        this.registros[ConstantesRegistros.PS.getCodigo()] = valor;
    }
    
    public void setES(int valor)
    {
        this.registros[ConstantesRegistros.ES.getCodigo()] = valor;
    }
    
    public void setSS(int valor)
    {
        this.registros[ConstantesRegistros.SS.getCodigo()] = valor;
    }
    
    public void setSP(int valor)
    {
        this.registros[ConstantesRegistros.SP.getCodigo()] = valor;
    }
    
    public void setOPC(int valor)
    {
        this.registros[ConstantesRegistros.OPC.getCodigo()] = valor;
    }
    
    public void setOP1(int valor)
    {
        this.registros[ConstantesRegistros.OP1.getCodigo()] = valor;
    }
    
    public void setOP2(int valor)
    {
        this.registros[ConstantesRegistros.OP2.getCodigo()] = valor;
    }
    
    public int getMBR()
    {
        return this.registros[ConstantesRegistros.MBR.getCodigo()];
    }
    
    public int getCS()
    {
        return this.registros[ConstantesRegistros.CS.getCodigo()];
    }

    public int getPS()
    {
        return this.registros[ConstantesRegistros.PS.getCodigo()];
    }
    
    public int getKS()
    {
        return this.registros[ConstantesRegistros.KS.getCodigo()];
    }
    
    public int getES()
    {
        return this.registros[ConstantesRegistros.ES.getCodigo()];
    }
    
     public int getSS()
    {
        return this.registros[ConstantesRegistros.SS.getCodigo()];
    }
     
      public int getSP()
    {
        return this.registros[ConstantesRegistros.SP.getCodigo()];
    }
    
    public int getIP()
    {
        return this.registros[ConstantesRegistros.IP.getCodigo()];
    }
    
    public int getOPC()
    {
        return this.registros[ConstantesRegistros.OPC.getCodigo()];
    }
    
    public int getOP1()
    {
        return this.registros[ConstantesRegistros.OP1.getCodigo()];
    }
    
    public int getOP2()
    {
        return this.registros[ConstantesRegistros.OP2.getCodigo()];
    }
      
    public int[] getRegistros()
    {
        return registros;
    }
    
    public byte[] getBytes()
    {
        ByteBuffer byteBuffer = ByteBuffer.allocate(this.registros.length * Integer.BYTES);
        for (int valor: this.registros)
            byteBuffer.putInt(valor);
        return byteBuffer.array();
    }

    public void setRegistros(int[] registros)
    {
        this.registros = registros;
    }
}
