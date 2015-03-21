xls = xlsread('readings.xlsx');

inputAngle = xls(:,1);
feedBackVoltage = xls(:,2);
guessedVoltage = xls(:,3);