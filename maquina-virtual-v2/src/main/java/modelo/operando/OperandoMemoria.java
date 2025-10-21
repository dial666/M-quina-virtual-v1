/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

import modelo.ConstantesRegistros;

/**
 *
 * @author valen
 */
public class OperandoMemoria extends Operando
{
    private int codTamanioCelda;
    private int codRegistro;
    private int offset;
    
    public OperandoMemoria(int operandoMemoria)
    {
        this.offset = (operandoMemoria << 16) >> 16;
        this.codRegistro = (operandoMemoria >> 16) & 0x1F;
        this.codTamanioCelda = (operandoMemoria >> 22) & 0x3;
    }

    public int getCodTamanioCelda()
    {
        return codTamanioCelda;
    }

    public int getCodRegistro()
    {
        return codRegistro;
    }

    public int getOffset()
    {
        return offset;
    }
      
    @Override
    public TipoOperando getTipo()
    {
        return TipoOperando.MEM;
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
        disassembler += tamanioCelda + "[" + ConstantesRegistros.getNombre(this.codRegistro);
        if (this.offset >= 0)
            disassembler += "+";
        disassembler += this.offset + "]";
        return disassembler;
    }
    
}
