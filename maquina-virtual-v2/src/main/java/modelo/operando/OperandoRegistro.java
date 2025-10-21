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
public class OperandoRegistro extends Operando
{
    private int codRegistro;
    private int codSector;
    
    public OperandoRegistro(int operandoRegistro)
    {
        this.codRegistro = operandoRegistro & 0x1F;
        this.codSector = (operandoRegistro >> 6) & 0x3;
    }

    public int getCodRegistro()
    {
        return codRegistro;
    }

    public int getCodSector()
    {
        return codSector;
    }

    @Override
    public TipoOperando getTipo()
    {
        return TipoOperando.REG;
    }

    @Override
    public String toString()
    {
        String disassembler;
        
        if (this.codRegistro >= ConstantesRegistros.EAX.getCodigo() && this.codRegistro <= ConstantesRegistros.EFX.getCodigo() && this.codSector != 0b00)
        {
            String letra = ConstantesRegistros.getNombre(this.codRegistro);
            letra = letra.substring(1, letra.length() - 1);
            disassembler = letra;
            disassembler += switch (this.codSector)
            {
                case 0b01 -> "L";
                case 0b10 -> "H";
                default -> "X";
            };
        }
        else
            disassembler = ConstantesRegistros.getNombre(this.codRegistro);
        return disassembler;
    }
}
