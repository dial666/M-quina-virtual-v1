/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;


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
        
}
