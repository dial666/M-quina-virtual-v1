/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operacion.OperacionFactory;
import modelo.operando.Operando;
import modelo.operando.OperandoFactory;

/**
 *
 * @author valen
 */
public class Instruccion
{
    private Operando opA;
    private Operando opB;
    private IOperacion op;
    
    public Instruccion(int codOp, int op1, int op2) throws VMException
    {
       this.opA = OperandoFactory.creaOperando(op1);
       this.opB = OperandoFactory.creaOperando(op2);
       this.op = OperacionFactory.creaOperacion(codOp);
    }
    
    public void ejecutar(UnidadIO mv) throws VMException
    {
        this.op.ejecutar(opA, opB, mv);
    }

    @Override
    public String toString()
    {
        String cadena = op.toString();
        if (opA != null)
            cadena += " " + opA.toString();
        if (opB != null)
            cadena += ", " + opB.toString();
        return cadena;
    }
    
    
}
