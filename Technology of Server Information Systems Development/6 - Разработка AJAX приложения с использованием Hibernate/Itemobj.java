package com.example.ThymeleafProject;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;

@Entity
public class ItemObj {
    @Id
    private int stockID;
    private String stock_name;
    private String purchase_date;

    public ItemObj() {}

    public ItemObj(int stockID, String stock_name, String purchase_date) {
        this.stockID = stockID;
        this.stock_name = stock_name;
        this.purchase_date = purchase_date;
    }

    public int getStockID() {
        return stockID;
    }

    public void setStockID(int stockID) {
        this.stockID = stockID;
    }

    public String getStock_name() {
        return stock_name;
    }

    public void setStock_name(String stock_name) {
        this.stock_name = stock_name;
    }

    public String getPurchase_date() {
        return purchase_date;
    }

    public void setPurchase_date(String purchase_date) {
        this.purchase_date = purchase_date;
    }

    @Override
    public String toString() {
        return "ItemObj{" +
                "stockID=" + stockID +
                ", stock_name='" + stock_name + '\'' +
                ", purchase_date='" + purchase_date + '\'' +
                '}';
    }
}

