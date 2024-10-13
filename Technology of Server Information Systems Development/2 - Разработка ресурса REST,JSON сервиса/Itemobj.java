package com.example.RestJavaProject1;
public class ItemObj {

    private String stock_name;
    private int stockID;
    private String purchase_date;

    // Конструктор
    public ItemObj(String stock_name, int stockID, String purchase_date) {
        this.stock_name = stock_name;
        this.stockID = stockID;
        this.purchase_date = purchase_date;
    }

    // Геттеры и сеттеры
    public String getStock_name() {
        return stock_name;
    }

    public void setStock_name(String stock_name) {
        this.stock_name = stock_name;
    }

    public int getStockID() {
        return stockID;
    }

    public void setStockID(int stockID) {
        this.stockID = stockID;
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
                "stock_name='" + stock_name + '\'' +
                ", stockID=" + stockID +
                ", purchase_date='" + purchase_date + '\'' +
                '}';
    }
}
