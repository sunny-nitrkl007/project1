from Config import*

workbook = xlrd.open_workbook(TEST_DATA)
sheet = workbook.sheet_by_index(0)

pidlist = sheet.ncols

wb = openpyxl.load_workbook(Input_file)
sheet1 = wb.get_sheet_by_name('Sheet1')

############################################
## Copy Test data from TEST_INPUT.xlsx
## to Input_data.xlsx by interchanging rows
############################################
for colidx in range(sheet.ncols):
    for rowidx in range(1,sheet.nrows):       
        sheet1.cell(row=colidx+2, column=rowidx+6).value = sheet.cell_value(rowidx,colidx)
        wb.save(Input_file)





