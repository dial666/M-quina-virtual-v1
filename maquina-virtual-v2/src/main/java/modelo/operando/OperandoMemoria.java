/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.ConstantesRegistros;
import modelo.Contexto;
import modelo.excepciones.SegmentationFaultException;

/**
 *
 * @author valen
 */
public class OperandoMemoria implements Operando
{
    private int codTamanioCelda;
    private OperandoRegistro operandoRegistro;
    private int offset;
    
    public OperandoMemoria(int codTamanioCelda, OperandoRegistro operandoRegistro, int offset)
    {
        this.offset = offset;
        this.operandoRegistro = operandoRegistro;
        this.codTamanioCelda = codTamanioCelda;
    }

    public int getCodTamanioCelda()
    {
        return codTamanioCelda;
    }

    public OperandoRegistro getOperandoRegistro()
    {
        return operandoRegistro;
    }

    public int getOffset()
    {
        return offset;
    }
 
    @Override
    public String toString()
    {
        String tamanioCelda;
        String disassembler = "";
        tamanioCelda = switch (this.codTamanioCelda)
        {
            case 0b11 -> "b";
            case 0b10 -> "w";
            default -> "l";
        };
        disassembler += tamanioCelda + "[" + ConstantesRegistros.getNombre(this.operandoRegistro.getCodRegistro());
        if (this.offset >= 0)
            disassembler += "+";
        disassembler += this.offset + "]";
        return disassembler;
    }

    @Override
    public int getValor(Contexto vmx) throws SegmentationFaultException
    {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public int setValor(Contexto vmx) throws SegmentationFaultException, IllegalArgumentException
    {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }
    
}
