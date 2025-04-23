from pgmpy.models import DiscreteBayesianNetwork
from pgmpy.factors.discrete import TabularCPD
from pgmpy.inference import VariableElimination

model = DiscreteBayesianNetwork([
    ('Flu', 'Fever'),
    ('Flu', 'Cough'),
    ('Allergy', 'Cough')
])

cpd_flu = TabularCPD('Flu', 2, [[0.9], [0.1]])
cpd_allergy = TabularCPD('Allergy', 2, [[0.7], [0.3]])

cpd_fever = TabularCPD(
    variable='Fever', variable_card=2,
    values=[[0.95, 0.2],  # P(Fever = 0 | Flu)
            [0.05, 0.8]], # P(Fever = 1 | Flu)
    evidence=['Flu'], evidence_card=[2]
)

cpd_cough = TabularCPD(
    variable='Cough', variable_card=2,
    values=[
        [0.99, 0.4, 0.5, 0.01],  # Cough = 0
        [0.01, 0.6, 0.5, 0.99]   # Cough = 1
    ],
    evidence=['Flu', 'Allergy'],
    evidence_card=[2, 2]
)

# Add CPDs and validate
model.add_cpds(cpd_flu, cpd_allergy, cpd_fever, cpd_cough)
print("Model is valid:", model.check_model())

# Inference
infer = VariableElimination(model)

# Query 1: What’s the probability of Flu given Fever and Cough?
result1 = infer.query(variables=['Flu'], evidence={'Fever': 1, 'Cough': 1})
print("\nP(Flu | Fever=1, Cough=1):")
print(result1)

# Query 2: What’s the probability of Allergy given Cough?
result2 = infer.query(variables=['Allergy'], evidence={'Cough': 1})
print("\nP(Allergy | Cough=1):")
print(result2)
