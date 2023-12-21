#include "stdafx.h"
#include "Caretaker.h"

Memento::Caretaker::Caretaker(
	AngularMeasurementsAndDates* aManuallyAngularMeasurementsAndDates,
	ObservationPoints* aManuallyObservationPoints,
	Outputs* aOutputVectorsAndOrbitalParameters) :
	m_pManuallyAngularMeasurementsAndDates(aManuallyAngularMeasurementsAndDates),
	m_pManuallyObservationPoints(aManuallyObservationPoints),
	m_pOutputVectorsAndOrbitalParameters(aOutputVectorsAndOrbitalParameters)
{
	this->ReadSettings();
};

Memento::Caretaker::~Caretaker()
{
	this->WriteSettings();
	for (auto* m : m_aAngularMeasurementsAndDates)
		delete m;
	for (auto* m : m_aObservationPoints)
		delete m;
	for (auto* m : m_aOutputs)
		delete m;
};

void Memento::Caretaker::ReadSettings()
{
	m_mementosSettings.beginGroup("/Cached parameters");

	int i = 0;
	int size = m_mementosSettings.beginReadArray("Angular measurements and dates");
	for (i = 0; i < size; i++)
	{
		m_mementosSettings.setArrayIndex(i);
		ConcreteMementoForManuallyAngularMeasurementsAndDates
			concreteMementoForManuallyAngularMeasurementsAndDates(
				m_mementosSettings.value("/alpha 1").toString(),
				m_mementosSettings.value("/delta 1").toString(),
				{	m_mementosSettings.value("/year 1", 2000).toInt(),
					m_mementosSettings.value("/month 1", 01).toInt(), 
					m_mementosSettings.value("/day 1", 01).toInt(), 
					m_mementosSettings.value("/hour 1", 00).toInt(), 
					m_mementosSettings.value("/minute 1", 00).toInt(), 
					m_mementosSettings.value("/second 1", 00).toInt() +
					m_mementosSettings.value("/millisecond 1", 000).toInt() / 1000.0 },
				m_mementosSettings.value("/alpha 2").toString(),
				m_mementosSettings.value("/delta 2").toString(),
				{	m_mementosSettings.value("/year 2", 2000).toInt(),
					m_mementosSettings.value("/month 2", 01).toInt(),
					m_mementosSettings.value("/day 2", 01).toInt(),
					m_mementosSettings.value("/hour 2", 00).toInt(),
					m_mementosSettings.value("/minute 2", 00).toInt(),
					m_mementosSettings.value("/second 2", 00).toInt() +
					m_mementosSettings.value("/millisecond 2", 000).toInt() / 1000.0 },
				m_mementosSettings.value("/alpha 3").toString(),
				m_mementosSettings.value("/delta 3").toString(),
				{	m_mementosSettings.value("/year 3", 2000).toInt(),
					m_mementosSettings.value("/month 3", 01).toInt(),
					m_mementosSettings.value("/day 3", 01).toInt(),
					m_mementosSettings.value("/hour 3", 00).toInt(),
					m_mementosSettings.value("/minute 3", 00).toInt(),
					m_mementosSettings.value("/second 3", 00).toInt() +
					m_mementosSettings.value("/millisecond 3", 000).toInt() / 1000.0 });
		m_aAngularMeasurementsAndDates.push_back(&concreteMementoForManuallyAngularMeasurementsAndDates);
	}
	m_mementosSettings.endArray();

	size = m_mementosSettings.beginReadArray("Observation points");
	for (i = 0; i < size; i++)
	{
		m_mementosSettings.setArrayIndex(i);
		ConcreteMementoForManuallyObservationPoints
			concreteMementoForManuallyObservationPoints(
				m_mementosSettings.value("/one observation point", false).toBool(),
				m_mementosSettings.value("/phi 1").toString(),
				m_mementosSettings.value("/lambda 1").toString(),
				m_mementosSettings.value("/H 1").toString(),
				m_mementosSettings.value("/phi 2").toString(),
				m_mementosSettings.value("/lambda 2").toString(),
				m_mementosSettings.value("/H 2").toString(), 
				m_mementosSettings.value("/phi 3").toString(),
				m_mementosSettings.value("/lambda 3").toString(),
				m_mementosSettings.value("/H 3").toString());
		m_aObservationPoints.push_back(&concreteMementoForManuallyObservationPoints);
	}
	m_mementosSettings.endArray();

	size = m_mementosSettings.beginReadArray("Outputs vectors and orbital parameters");
	for (i = 0; i < size; i++)
	{
		m_mementosSettings.setArrayIndex(i);
		ConcreteMementoForOutputVectorsAndOrbitalParameters
			concreteMementoForOutputVectorsAndOrbitalParameters(
				m_mementosSettings.value("/method name").toString(),
				m_mementosSettings.value("/r_2").toString(),
				m_mementosSettings.value("/v_2").toString(), 
				m_mementosSettings.value("/inclination").toString(), 
				m_mementosSettings.value("/right ascention of the ascending node").toString(),
				m_mementosSettings.value("/argument of perigee").toString(),
				m_mementosSettings.value("/eccentricity").toString(),
				m_mementosSettings.value("/large semi-axis").toString(),
				m_mementosSettings.value("/true anomaly").toString(),
				m_mementosSettings.value("/angular momentum").toString());
		m_aOutputs.push_back(&concreteMementoForOutputVectorsAndOrbitalParameters);
	}
	m_mementosSettings.endArray();

	m_mementosSettings.endGroup();
};

void Memento::Caretaker::WriteSettings()
{
	m_mementosSettings.beginGroup("/Cached parameters");

	int i = 0;
	m_mementosSettings.beginWriteArray("Angular measurements and dates");
	for (i = 0; i < m_aAngularMeasurementsAndDates.size(); i++)
	{
		m_mementosSettings.setArrayIndex(i);
		m_mementosSettings.setValue("/alpha 1", m_aAngularMeasurementsAndDates.at(i)->GetAlpha1());
		m_mementosSettings.setValue("/delta 1", m_aAngularMeasurementsAndDates.at(i)->GetDelta1());

		m_mementosSettings.setValue("/year 1", m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().year);
		m_mementosSettings.setValue("/month 1", m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().month);
		m_mementosSettings.setValue("/day 1", m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().day);
		m_mementosSettings.setValue("/hour 1", m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().hour);
		m_mementosSettings.setValue("/minute 1", m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().min);
		m_mementosSettings.setValue("/second 1", static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().sec));
		m_mementosSettings.setValue("/millisecond 1", 1000 * (m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().sec -
			static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime1().sec)));

		m_mementosSettings.setValue("/alpha 2", m_aAngularMeasurementsAndDates.at(i)->GetAlpha2());
		m_mementosSettings.setValue("/delta 2", m_aAngularMeasurementsAndDates.at(i)->GetDelta2());

		m_mementosSettings.setValue("/year 2", m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().year);
		m_mementosSettings.setValue("/month 2", m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().month);
		m_mementosSettings.setValue("/day 2", m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().day);
		m_mementosSettings.setValue("/hour 2", m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().hour);
		m_mementosSettings.setValue("/minute 2", m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().min);
		m_mementosSettings.setValue("/second 2", static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().sec));
		m_mementosSettings.setValue("/millisecond 2", 1000 * (m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().sec -
			static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime2().sec)));

		m_mementosSettings.setValue("/alpha 3", m_aAngularMeasurementsAndDates.at(i)->GetAlpha3());
		m_mementosSettings.setValue("/delta 3", m_aAngularMeasurementsAndDates.at(i)->GetDelta3());

		m_mementosSettings.setValue("/year 3", m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().year);
		m_mementosSettings.setValue("/month 3", m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().month);
		m_mementosSettings.setValue("/day 3", m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().day);
		m_mementosSettings.setValue("/hour 3", m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().hour);
		m_mementosSettings.setValue("/minute 3", m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().min);
		m_mementosSettings.setValue("/second 3", static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().sec));
		m_mementosSettings.setValue("/millisecond 3", 1000 * (m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().sec -
			static_cast<int>(m_aAngularMeasurementsAndDates.at(i)->GetDateTime3().sec)));
	}
	m_mementosSettings.endArray();

	m_mementosSettings.beginWriteArray("Observation points");
	for (i = 0; i < m_aObservationPoints.size(); i++)
	{
		m_mementosSettings.setArrayIndex(i);
		
		m_mementosSettings.setValue("/one observation point", m_aObservationPoints.at(i)->IsOneObservationPoint());
		m_mementosSettings.setValue("/phi 1", m_aObservationPoints.at(i)->GetPhi1());
		m_mementosSettings.setValue("/lambda 1", m_aObservationPoints.at(i)->GetLambda1());
		m_mementosSettings.setValue("/H 1", m_aObservationPoints.at(i)->GetH1());

		m_mementosSettings.setValue("/phi 2", m_aObservationPoints.at(i)->GetPhi2());
		m_mementosSettings.setValue("/lambda 2", m_aObservationPoints.at(i)->GetLambda2());
		m_mementosSettings.setValue("/H 2", m_aObservationPoints.at(i)->GetH2());

		m_mementosSettings.setValue("/phi 3", m_aObservationPoints.at(i)->GetPhi3());
		m_mementosSettings.setValue("/lambda 3", m_aObservationPoints.at(i)->GetLambda3());
		m_mementosSettings.setValue("/H 3", m_aObservationPoints.at(i)->GetH3());
	}
	m_mementosSettings.endArray();

	m_mementosSettings.beginWriteArray("Outputs vectors and orbital parameters");
	for (i = 0; i < m_aOutputs.size(); i++)
	{
		m_mementosSettings.setArrayIndex(i);
		m_mementosSettings.setValue("/method name", m_aOutputs.at(i)->GetMethodName());
		m_mementosSettings.setValue("/r_2", m_aOutputs.at(i)->Get_r_2());
		m_mementosSettings.setValue("/v_2", m_aOutputs.at(i)->Get_v_2());
		m_mementosSettings.setValue("/inclination", m_aOutputs.at(i)->GetInclination());
		m_mementosSettings.setValue("/right ascention of the ascending node", m_aOutputs.at(i)->GetRightAscentionOfTheAscendingNode());
		m_mementosSettings.setValue("/argument of perigee", m_aOutputs.at(i)->GetArgumentOfPerigee());
		m_mementosSettings.setValue("/eccentricity", m_aOutputs.at(i)->GetEccentricity());
		m_mementosSettings.setValue("/large semi-axis", m_aOutputs.at(i)->GetLargeSemiaxis());
		m_mementosSettings.setValue("/true anomaly", m_aOutputs.at(i)->GetTrueAnomaly());
		m_mementosSettings.setValue("/angular momentum", m_aOutputs.at(i)->GetAngularMomentum());
	}
	m_mementosSettings.endArray();

	m_mementosSettings.endGroup();
};

void Memento::Caretaker::Backup()
{
	ConcreteMementoForManuallyAngularMeasurementsAndDates* pAngularMeasurementsAndDatesMemento =
		this->m_pManuallyAngularMeasurementsAndDates->Save();
	ConcreteMementoForManuallyObservationPoints* pObservationPointsMemento =
		this->m_pManuallyObservationPoints->Save();
	ConcreteMementoForOutputVectorsAndOrbitalParameters* pOutputVectorsAndOrbitalParameters =
		this->m_pOutputVectorsAndOrbitalParameters->Save();
	if (!std::any_of(m_aAngularMeasurementsAndDates.begin(), m_aAngularMeasurementsAndDates.end(),
			[&](ConcreteMementoForManuallyAngularMeasurementsAndDates* memento) {
				return (*memento == *pAngularMeasurementsAndDatesMemento); }) &&
		!std::any_of(m_aObservationPoints.begin(), m_aObservationPoints.end(),
			[&](ConcreteMementoForManuallyObservationPoints* memento) {
				return (*memento == *pObservationPointsMemento); }) &&
		!std::any_of(m_aOutputs.begin(), m_aOutputs.end(),
			[&](ConcreteMementoForOutputVectorsAndOrbitalParameters* memento) {
				return (*memento == *pOutputVectorsAndOrbitalParameters); }))
	{
		this->m_aAngularMeasurementsAndDates.push_back(pAngularMeasurementsAndDatesMemento);
		this->m_aObservationPoints.push_back(pObservationPointsMemento);
		this->m_aOutputs.push_back(pOutputVectorsAndOrbitalParameters);
	}
};

void Memento::Caretaker::Undo(int index)
{
	if (this->m_aAngularMeasurementsAndDates.empty() &&
		this->m_aObservationPoints.empty() &&
		this->m_aOutputs.empty())
		return;

	ConcreteMementoForManuallyAngularMeasurementsAndDates* pAngularMeasurementsAndDatesMemento =
		this->m_aAngularMeasurementsAndDates.at(index);
	this->m_aAngularMeasurementsAndDates.erase(m_aAngularMeasurementsAndDates.begin() + index);
	ConcreteMementoForManuallyObservationPoints* pObservationPointsMemento =
		this->m_aObservationPoints.at(index);
	this->m_aObservationPoints.erase(m_aObservationPoints.begin() + index);
	ConcreteMementoForOutputVectorsAndOrbitalParameters* pOutputVectorsAndOrbitalParameters =
		this->m_aOutputs.at(index);
	this->m_aOutputs.erase(m_aOutputs.begin() + index);

	this->m_pManuallyAngularMeasurementsAndDates->Restore(pAngularMeasurementsAndDatesMemento);
	this->m_pManuallyObservationPoints->Restore(pObservationPointsMemento);
	this->m_pOutputVectorsAndOrbitalParameters->Restore(pOutputVectorsAndOrbitalParameters);
};

const QVector<Memento::ConcreteMementoForManuallyAngularMeasurementsAndDates*>&
Memento::Caretaker::GetVectorOfAngularMeasurementsAndDatesMementos()
{
	return this->m_aAngularMeasurementsAndDates;
};

const QVector<Memento::ConcreteMementoForManuallyObservationPoints*>&
Memento::Caretaker::GetVectorOfObservationPointsMementos()
{
	return this->m_aObservationPoints;
};

const QVector<Memento::ConcreteMementoForOutputVectorsAndOrbitalParameters*>&
Memento::Caretaker::GetVectorOfOutputParametersMementos()
{
	return this->m_aOutputs;
};