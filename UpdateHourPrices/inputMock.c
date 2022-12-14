#include "../Loxone.Common/inputMock.h"
#include "../Loxone.Common/loxoneTime.h"

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

int timeState = 0;
time_t seconds = NULL;

unsigned int getcurrenttimemock()
{
    if (seconds == NULL) {
        seconds = time(NULL);
    }
    else {
        seconds = seconds + 60;
    }

    return seconds;
}

float getiomock(char* str)
{
	if (strstr(str, "VI1") != NULL) { return 0.0f; } // VI1 Virtual input 1
	else if (strstr(str, "VI2") != NULL) { return 0.0f; } // VI2 Virtual input 2

	return 0.0f;
}

int getinputeventmock()
{
	return 0x02; // Input 2 has changed
}

float getinputmock(int input)
{
	if (input == 0) { return 1.25f; } // Input  1
	else if (input == 1) { return 0.0f; } // Input  2
	else if (input == 2) { return 0.0f; } // Input  3
	else if (input == 3) { return 0.0f; } // Input  4
	else if (input == 4) { return 0.0f; } // Input  5
	else if (input == 5) { return 0.0f; } // Input  6
	else if (input == 6) { return 0.0f; } // Input  7
	else if (input == 7) { return 0.0f; } // Input  8
	else if (input == 8) { return 0.0f; } // Input  9
	else if (input == 9) { return 0.0f; } // Input 10
	else if (input == 10) { return 0.0f; } // Input 11
	else if (input == 11) { return 0.0f; } // Input 12
	else if (input == 12) { return 0.0f; } // Input 13

	return 0.0f;
}

char* getinputtextmock(int input)
{
	if (input == 0) { return ""; } // Text input 1
	else if (input == 1) { return ""; } // Text input 2
	else if (input == 2) { return ""; } // Text input 3

	return NULL;
}

char* httpgetmock(char* adress, char* page) {
	if (strstr(page, "AveragePrices") != NULL) {
		return "\
<GetAveragePricesResult xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd = \"http://www.w3.org/2001/XMLSchema\">\r\n\
    <Today>0.72445</Today>\r\n\
    <Week>0.72445</Week>\r\n\
    <Month>0.72445</Month>\r\n\
    <Last7Days>1.1092743</Last7Days>\r\n\
    <Last31Days>1.3020128</Last31Days>\r\n\
    <PriceUnit>NOK/kWh</PriceUnit>\r\n\
</GetAveragePricesResult>";
	}



	else if (strstr(page, "PriceScoreToday") != NULL) {
		return "\
<GetScoreResult xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n\
    <ScoreNow>10</ScoreNow>\r\n\
    <HourNow>12</HourNow>\r\n\
    <PriceNow>1.02695</PriceNow>\r\n\
    <PriceUnit>NOK/kWh</PriceUnit>\r\n\
    <HourScores>\r\n\
        <ScoreOfHour0>9</ScoreOfHour0>\r\n\
        <ScoreOfHour1>7</ScoreOfHour1>\r\n\
        <ScoreOfHour2>4</ScoreOfHour2>\r\n\
        <ScoreOfHour3>1</ScoreOfHour3>\r\n\
        <ScoreOfHour4>2</ScoreOfHour4>\r\n\
        <ScoreOfHour5>3</ScoreOfHour5>\r\n\
        <ScoreOfHour6>6</ScoreOfHour6>\r\n\
        <ScoreOfHour7>15</ScoreOfHour7>\r\n\
        <ScoreOfHour8>17</ScoreOfHour8>\r\n\
        <ScoreOfHour9>12</ScoreOfHour9>\r\n\
        <ScoreOfHour10>8</ScoreOfHour10>\r\n\
        <ScoreOfHour11>11</ScoreOfHour11>\r\n\
        <ScoreOfHour12>10</ScoreOfHour12>\r\n\
        <ScoreOfHour13>13</ScoreOfHour13>\r\n\
        <ScoreOfHour14>16</ScoreOfHour14>\r\n\
        <ScoreOfHour15>18</ScoreOfHour15>\r\n\
        <ScoreOfHour16>21</ScoreOfHour16>\r\n\
        <ScoreOfHour17>23</ScoreOfHour17>\r\n\
        <ScoreOfHour18>25</ScoreOfHour18>\r\n\
        <ScoreOfHour19>24</ScoreOfHour19>\r\n\
        <ScoreOfHour20>22</ScoreOfHour20>\r\n\
        <ScoreOfHour21>20</ScoreOfHour21>\r\n\
        <ScoreOfHour22>19</ScoreOfHour22>\r\n\
        <ScoreOfHour23>14</ScoreOfHour23>\r\n\
    </HourScores>\r\n\
    <HourPrices>\r\n\
        <PriceOfHour0>1.0268472</PriceOfHour0>\r\n\
        <PriceOfHour1>1.0053841</PriceOfHour1>\r\n\
        <PriceOfHour2>1.0027139</PriceOfHour2>\r\n\
        <PriceOfHour3>0.9803264</PriceOfHour3>\r\n\
        <PriceOfHour4>0.9817642</PriceOfHour4>\r\n\
        <PriceOfHour5>0.98700166</PriceOfHour5>\r\n\
        <PriceOfHour6>1.0048705</PriceOfHour6>\r\n\
        <PriceOfHour7>1.0950367</PriceOfHour7>\r\n\
        <PriceOfHour8>1.1277965</PriceOfHour8>\r\n\
        <PriceOfHour9>1.0484132</PriceOfHour9>\r\n\
        <PriceOfHour10>1.025923</PriceOfHour10>\r\n\
        <PriceOfHour11>1.027258</PriceOfHour11>\r\n\
        <PriceOfHour12>1.02695</PriceOfHour12>\r\n\
        <PriceOfHour13>1.0539588</PriceOfHour13>\r\n\
        <PriceOfHour14>1.0967827</PriceOfHour14>\r\n\
        <PriceOfHour15>1.2489766</PriceOfHour15>\r\n\
        <PriceOfHour16>1.3920307</PriceOfHour16>\r\n\
        <PriceOfHour17>1.5523376</PriceOfHour17>\r\n\
        <PriceOfHour18>1.6937485</PriceOfHour18>\r\n\
        <PriceOfHour19>1.6402445</PriceOfHour19>\r\n\
        <PriceOfHour20>1.4664845</PriceOfHour20>\r\n\
        <PriceOfHour21>1.3827881</PriceOfHour21>\r\n\
        <PriceOfHour22>1.2637646</PriceOfHour22>\r\n\
        <PriceOfHour23>1.087232</PriceOfHour23>\r\n\
    </HourPrices>\r\n\
</GetScoreResult>";
	}

    else if (strstr(page, "PriceScoreTomorrow") != NULL) {
        return "\
<GetScoreResult xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\r\n\
    <ScoreNow>15</ScoreNow>\r\n\
    <HourNow>19</HourNow>\r\n\
    <PriceNow>0.98169607</PriceNow>\r\n\
    <PriceUnit>NOK/kWh</PriceUnit>\r\n\
    <HourScores>\r\n\
        <ScoreOfHour0>6</ScoreOfHour0>\r\n\
        <ScoreOfHour1>4</ScoreOfHour1>\r\n\
        <ScoreOfHour2>1</ScoreOfHour2>\r\n\
        <ScoreOfHour3>2</ScoreOfHour3>\r\n\
        <ScoreOfHour4>3</ScoreOfHour4>\r\n\
        <ScoreOfHour5>5</ScoreOfHour5>\r\n\
        <ScoreOfHour6>7</ScoreOfHour6>\r\n\
        <ScoreOfHour7>10</ScoreOfHour7>\r\n\
        <ScoreOfHour8>9</ScoreOfHour8>\r\n\
        <ScoreOfHour9>11</ScoreOfHour9>\r\n\
        <ScoreOfHour10>12</ScoreOfHour10>\r\n\
        <ScoreOfHour11>18</ScoreOfHour11>\r\n\
        <ScoreOfHour12>17</ScoreOfHour12>\r\n\
        <ScoreOfHour13>20</ScoreOfHour13>\r\n\
        <ScoreOfHour14>21</ScoreOfHour14>\r\n\
        <ScoreOfHour15>19</ScoreOfHour15>\r\n\
        <ScoreOfHour16>23</ScoreOfHour16>\r\n\
        <ScoreOfHour17>24</ScoreOfHour17>\r\n\
        <ScoreOfHour18>22</ScoreOfHour18>\r\n\
        <ScoreOfHour19>15</ScoreOfHour19>\r\n\
        <ScoreOfHour20>14</ScoreOfHour20>\r\n\
        <ScoreOfHour21>13</ScoreOfHour21>\r\n\
        <ScoreOfHour22>16</ScoreOfHour22>\r\n\
        <ScoreOfHour23>8</ScoreOfHour23>\r\n\
    </HourScores>\r\n\
    <HourPrices>\r\n\
        <PriceOfHour0>0.6844638</PriceOfHour0>\r\n\
        <PriceOfHour1>0.474466</PriceOfHour1>\r\n\
        <PriceOfHour2>0.39880127</PriceOfHour2>\r\n\
        <PriceOfHour3>0.41170213</PriceOfHour3>\r\n\
        <PriceOfHour4>0.43484184</PriceOfHour4>\r\n\
        <PriceOfHour5>0.5272982</PriceOfHour5>\r\n\
        <PriceOfHour6>0.7781488</PriceOfHour6>\r\n\
        <PriceOfHour7>0.8928233</PriceOfHour7>\r\n\
        <PriceOfHour8>0.8603664</PriceOfHour8>\r\n\
        <PriceOfHour9>0.9202633</PriceOfHour9>\r\n\
        <PriceOfHour10>0.9340858</PriceOfHour10>\r\n\
        <PriceOfHour11>1.0500913</PriceOfHour11>\r\n\
        <PriceOfHour12>1.0303304</PriceOfHour12>\r\n\
        <PriceOfHour13>1.0941181</PriceOfHour13>\r\n\
        <PriceOfHour14>1.095142</PriceOfHour14>\r\n\
        <PriceOfHour15>1.0537772</PriceOfHour15>\r\n\
        <PriceOfHour16>1.1050737</PriceOfHour16>\r\n\
        <PriceOfHour17>1.1862674</PriceOfHour17>\r\n\
        <PriceOfHour18>1.0970875</PriceOfHour18>\r\n\
        <PriceOfHour19>0.98169607</PriceOfHour19>\r\n\
        <PriceOfHour20>0.9528227</PriceOfHour20>\r\n\
        <PriceOfHour21>0.9450413</PriceOfHour21>\r\n\
        <PriceOfHour22>0.98323196</PriceOfHour22>\r\n\
        <PriceOfHour23>0.8599568</PriceOfHour23>\r\n\
    </HourPrices>\r\n\
</GetScoreResult>";
    }

    

	return NULL;
}