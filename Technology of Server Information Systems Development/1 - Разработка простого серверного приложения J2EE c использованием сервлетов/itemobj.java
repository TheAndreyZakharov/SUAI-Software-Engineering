package servlet;

public class ItemObj {
    private String stock_name;
    private String stockID;
    private String purchase_date;

    public ItemObj(String stock_name, String stockID, String purchase_date) {
        this.stock_name = stock_name;
        this.stockID = stockID;
        this.purchase_date = purchase_date;
    }

    public String getStock_name() {
        return stock_name;
    }

    public void setStock_name(String stock_name) {
        this.stock_name = stock_name;
    }

    public String getStockID() {
        return stockID;
    }

    public void setStockID(String stockID) {
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
        return "Название акции: " + stock_name + ", ID акции: " + stockID + ", Дата покупки: " + purchase_date;
    }
}
