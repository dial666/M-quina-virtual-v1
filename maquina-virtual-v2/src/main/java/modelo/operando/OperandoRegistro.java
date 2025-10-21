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
public abstract class OperandoRegistro extends Operando
{
    private int codRegistro;
    private int mask;
    private int shift;
    
    public OperandoRegistro(int codRegistro, int mask, int shift)
    {
        this.codRegistro = codRegistro;
        this.mask = mask;
        this.shift = shift;
    }

    public int getCodRegistro()
    {
        return codRegistro;
    }

    public int getMask()
    {
        return mask;
    }

    public int getShift()
    {
        return shift;
    }
}
