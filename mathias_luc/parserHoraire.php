<?php
function parserHoraire()
{
	//tableau [ligne][a ou r][v]
	//array ( "tdep" => "t0", "hdep" => "8:42","tarr" => "t1", "harr" => "8:50" )
	
	$tabHoraire= array(array(array()));
	
	$ligne = 1; // compteur de ligne
	$fic = fopen("horaires.csv", "a+");
	$sense="a";
	$lignePrec=0;
	$lignesDuFichierPrecedent = array();
	//$i = element de la ligne 
	//recuperer une ligne du fichier csv
	while($tab=fgetcsv($fic,0,','))
	{
		$champs = count($tab);//nombre de champ dans la ligne en question
		$ligne ++;
		
	if($tab[0][0] == 'l')
		{
			$tmp=explode(" ",$tab[0]);
			$ligneDeBus=$tmp[1];
			
			
			$tabHoraire[0]=$ligneDeBus;
			//tester si c'est l'aller ou le retour
			$lignePrec==$ligneDeBus? $sense="r" : $sense="a";
			//enregistrer la ligne prec;
			$lignePrec=$ligneDeBus;
			$nbArret=0;
		}
		
		if($tab[0][0] =="T")
		{
			$lignesDuFichierPrecedent[]=$tab;
			
		}
		
		if($tab[0][0] == 'D')
		{
			
			$nbTerminus=count($lignesDuFichierPrecedent);
			$tDepartTmp=NULL;
			$terminusDepart=NULL;
			//j= indice de la ligne de bus
			$l=0;
			//pour la ligne du fichier precedent en cours
			//k = indice des elements
			for($k=1;$k<count($lignesDuFichierPrecedent[$l]);$k++)
			{
				//parcourir les precedentes lignes pour savoir quel couple de terminus il faut conserver
				//terminus depart
				for($j=0; $j<$nbTerminus ; $j++)
				{
					if(isset($lignesDuFichierPrecedent[$j][$k]) &&  $lignesDuFichierPrecedent[$j][$k]!="")
					{
						$minutes=strstr($lignesDuFichierPrecedent[$j][$k],":");
						$heureEnMinute=strstr($lignesDuFichierPrecedent[$j][$k],":",true)*60;
						$heureEnMinute+=$minutes[1]*10+$minutes[2];
						
						$tDepartTmp=$heureEnMinute;
						$terminusDepart=$lignesDuFichierPrecedent[$j][0];
						
						break;
					}
				
				}
				//pour les terminus arriver
				for($j=$nbTerminus-1; $j>=0 ; $j--)
				{
					if(isset($lignesDuFichierPrecedent[$j][$k]) &&  $lignesDuFichierPrecedent[$j][$k]!="")
					{
						$minutes=strstr($lignesDuFichierPrecedent[$j][$k],":");
						$heureEnMinute=strstr($lignesDuFichierPrecedent[$j][$k],":",true)*60;
						$heureEnMinute+=$minutes[1]*10+$minutes[2];

						$tArriveTmp=$heureEnMinute;
						
						$terminusArriver=$lignesDuFichierPrecedent[$j][0];
						
						break;
					}
				
				}
				
				$tabHoraire[$ligneDeBus][$sense][$k]["td"]=$terminusDepart;
				$tabHoraire[$ligneDeBus][$sense][$k]["hd"]=$tDepartTmp;
				$tabHoraire[$ligneDeBus][$sense][$k]["ta"]=$terminusArriver;
				$tabHoraire[$ligneDeBus][$sense][$k]["ha"]=$tArriveTmp;
				$tabHoraire[$ligneDeBus][$sense][$k]["d"]=$tab[$k];
				
			
			}
			
			
			$lignesDuFichierPrecedent=NULL;
		}
		

	}
return $tabHoraire;
			
}

?> 