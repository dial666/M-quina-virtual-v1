/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.operacion.jump;

import modelo.ConstantesRegistros;
import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operacion.IOperacion;
import modelo.operando.Operando;
import modelo.operando.OperandoRegistro;
import modelo.operando.OperandoRegistroE;

/**
 *
 * @author valen
 */
public abstract class OperacionJump implements IOperacion
{
    private int valorCC_n;
    private int valorCC_z;
    
    @Override
    public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException
    {
       int valorCC = new OperandoRegistroE(ConstantesRegistros.CC.getCodigo()).getValor(mv);
       this.valorCC_n = (valorCC >> 31) & 0b01;
       this.valorCC_z = (valorCC >> 30) & 0b01;
       
       if (saltar())
       {
           Operando opIP = new OperandoRegistroE(ConstantesRegistros.IP.getCodigo());
           Operando opCS = new OperandoRegistroE(ConstantesRegistros.CS.getCodigo());
           
           opIP.setValor(mv, opCS.getValor(mv) + opA.getValor(mv));
       }
    }
    
    protected boolean jmpIf(int n, int z)
    {
        return (this.valorCC_n == n) && (this.valorCC_z == z);
    }
    
    public abstract boolean saltar();
}
