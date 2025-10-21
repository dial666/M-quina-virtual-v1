/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operando;

/**
 *
 * @author valen
 */
public class OperandoInmediato extends Operando
{
    private int valor;
    
    public OperandoInmediato(int operandoInmediato)
    {
        this.valor = operandoInmediato;
    }
    
    @Override
    public TipoOperando getTipo()
    {
        return TipoOperando.INM;
    }

    @Override
    public String toString()
    {
        return "" + this.valor;
    }
    
}
