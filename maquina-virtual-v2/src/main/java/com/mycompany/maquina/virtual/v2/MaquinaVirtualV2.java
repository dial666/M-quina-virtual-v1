/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 */

package com.mycompany.maquina.virtual.v2;

import modelo.operando.Operando;
import modelo.operando.OperandoMemoria;
import modelo.operando.OperandoRegistro;

/**
 *
 * @author valen
 */
public class MaquinaVirtualV2 {

    public static void main(String[] args) {
        Operando opm = Operando.creaOperando(3, 0x0AFFFE);
        Operando opr = Operando.creaOperando(1, 0x4F);
        Operando opi = Operando.creaOperando(2, 0xFFFFFFF4);
        System.out.println(opm);
        System.out.println(opr);
        System.out.println(opi);
    }
}
