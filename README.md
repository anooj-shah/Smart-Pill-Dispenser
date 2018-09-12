
# Smart Pill Dispenser
##### An IoT device that solves the problem of medical adherence
##### By Anooj Shah
##### Under the guidance of: Tim McConnell
## Table of Contents  
* [The Problem](#the-problem)
* [Existing Solutions](#existing-solutions)
* [Technical Interviews](#technical-interviews-computer)
* [Resume](#resume-books)
  * [Building Your Resume](#building-your-resume)
  * [Resume Design](#resume-design)
  * [Resume Feedback](#resume-feedback)
* [Cover Letters](#cover-letters-love-letter)
* [Referrals](#referrals-grin-heart-grin)
* [Fellowships](#fellowships-rocket)
* [Networking](#networking-zap)
  * [Social Networking](#social-networking-resources)
* [Keeping Track of Your Applications](#keeping-track-of-your-applications-pencil)
* [Portfolio and Profile](#portfolio-and-profile-loudspeaker)

## The Problem
Patients not taking their medicines correctly and on time is referred to as the “Medication Adherence” problem. It is a “health care-oriented term that has various definitions across the medical community” (Dudzinski 1). The broad definition refers to the “extent that a person’s behavior, such as taking medications, following a diet, and/or executing lifestyle changes, corresponds with agreed recommendations from a healthcare provider" (Sabaté 3).

Common reasons for the medication adherence problem are related to patient behaviors such as forgetfulness, running out of medication, and carelessness. “Out of the three, the most commonly reported means of non-adherence was forgetfulness” (Dudzinski 1).

The negative effects of the lack of medication adherence include high health care costs, increased patient discomfort, and shorter lifespans. “With older populations, it is reported that compliance rates range roughly from 38% to 57%, with an average rate of less than 45%. For the elderly patient, medication issues and/or abuses may also result in accidents, such as a fall that causes a hip fracture. Furthermore, an elderly patient could forget that he or she had already taken the prescribed amount of medication and unwittingly overdose” (Gottlieb 1). The results are “hospital admissions, prolonged hospital stay, additional resource utilization, and time away from work, as well as lower patient satisfaction” (Morimoto, T, T K Gandhi, A C Seger, T C Hsieh, D. W Bates 306).

Medication adherence can have a significant effect on improving treatments for patients. Its importance cannot be understated. “Increasing the effectiveness of adherence interventions may have a far greater impact on the health of the population than any improvement in specific medical treatments” (Brown and Bussell 304).

## EXISTING SOLUTIONS :sol:
 Research in the area of medication adherence is lacking. “While patient non-adherence to medication regimens remains one of the most important health care concerns, it is surprising that research in this area is sorely lacking” (Gottlieb 5). Current solutions to the problem are limited. 

Below are a few solutions that have attempted to address the problem:

•	Vitality GlowCaps medicine dispenser bottles is a product mentioned in IoT (Internet of Things) literature (Swan 241). The cap of the dispenser bottle has a chip which monitors when the pill bottle is opened and wirelessly relays alerts through the AT&T Mobile Broadband Network to the patient and the caregiver. This would have been a good product to evaluate. However, it appears to be discontinued according to the company’s web site (http://www.vitality.net/).

•	MD2 Plus electronic pill dispenser (http://www.epill.com/md2plus.html): This is a bulky piece of equipment and does not appear to have convenient notification capabilities. Other products (MD1, MD2, MD3) from the same manufacturer appear to have similar limitations although they all have the ability to notify via an audible alarm.

•	Examples of other products are the “Ivation Automatic Pill Dispenser” (http://myivation.com/index.php/ivation-pill-dispenser-tray.html) and “Med-e-lert Automatic Pill Dispenser” (http://www.medelert.net) which are also limited in functionality. They provide automatic reminders or alarms but do not have the capability to interface with email or text messaging systems.

## PROPOSED SOLUTION
### Product Description
 Patients, especially the elderly forget to take their medicine at the appropriate time and as prescribed. The “Smart Medicine Dispenser” will aid patients in this regard by providing a solution for dispensing medicines properly and tracking their medicine taking activities. It is assumed that a patient has taken his medicine after it is dispensed.

### The Smart Medicine Dispenser will have the following capabilities:

•	Alerting: This feature will alert patients when it is time for them to take their medicines so that they can press the “Dispense” button on their medicine dispenser. A patient is alerted with a sound as well as LED lights.
•	Smart dispensing: Dispense different medicines. The medicines will be in the form of pills. Each medicine will be placed in a separate compartment. When the “Dispense” button is pressed, the medicines will be dispensed from each compartment in the correct quantities.
•	Smart notification: If the medicines are not dispensed on time, notifications will be sent to specified people in the form of an email, text message and a phone call. For example, a notification can be sent to the patient and designated family members.
•	Recording: The system will record events and activities in a database. An event relates to the scenario of medicines not being dispensed at the specified time. An activity refers to the act of medicines being dispensed. Note that it is assumed that a patient has taken his medicine after dispensing it. The event and activity data this stored can be analyzed periodically to report on how a patient is adhering to his routine of taking medicines. This will result in better awareness which in turn will lead to improving medication adherence.
The following diagram depicts the above process:


Below is a schematic of the Smart Medicine Dispenser. The LED lights and speaker are for alerting patients when it is time to take their medicine. The Tower Pro SG92R Micro Servos allow us to programmatically control the motion of the underlying motors. There is a Micro Servo for each pill compartment. When the patient presses the Dispense button, the Micro servos cause their respective motors to rotate as required and dispense the pills appropriately. The screen is a display monitor. All of the parts are available and have to be assembled. The adjustable pill holder is something that needs to be designed and created.
![pillsketch](https://user-images.githubusercontent.com/18583623/45432383-58120080-b66f-11e8-9c60-2bfeed7ed505.png)


### Product Target Audience
 The Smart Medicine Dispenser can be used by patients in need of tracking their routine of taking medicines. It will be particularly useful for the elderly who are more impacted by the medication adherence problem. The target audience can also include health care practitioners and family members close to the patient. The reporting capability would be especially useful for health care practitioners in treating their patients.

Taking the United States as an example, the target patient population is substantial. Based on US census data, about 14.9% of the population is 65 years or older. Assuming the total population to be 320 million, this amounts to 48 million people. In Canada, 2011 census reports estimate 5 million people in Canada were 65 or older in 2011. 

### Product Advantages
•	The Smart Medicine Dispenser will be affordable as it will be made from lost cost electronic components. 
•	It will alert patients when it is time to take their medicine. The alerts will use simple mechanisms like sound and lights. They not use text messaging or emails so that patients are not burdened with the task of managing many messages and emails. It is also assumed that not everyone will want to receive frequent text messages because of the possibility of being charged per message. 
•	When a medicine is not taken within a few minutes of being alerted, an event will be generated. The event will send notifications using text messaging, emails and phone calls. This should be acceptable, though because it is expected that non-adherence should be an exception. 
•	A web page will provide the ability to patients and designated people to view all current and past data. It will also allow one to update the status of an event as needed. 
•	Having access to the data generated by the product will be valuable. The product will provide a simple report based on individual usage in order to demonstrate the overall concept.
•	The capability to run reports on historical data will be a good indicator of past behavior. It will be useful to patients and health practitioners. The data will cause patients to become more vigilant and improve medication adherence.

### Product Limitations 
The product will be more of a prototype and will not have the look and feel and convenience of a finished product. Below are some of the limitations the product will have. These limitations can be overcome as more time becomes available and the product is enhanced in the future.

•	Initially, the smart medicine dispenser will not have the functionality to send alerts when it is time to refill a compartment with medicine. However, this feature can be included in the future by placing appropriate sensors in the individual medicine compartments. Another way to address this limitation is to employ a disciplined process to refill on a designated day each month.
•	We may have to limit the number of medicines to one or two because each compartment will require its own motor and hardware. The support for more medicines with additional compartments can be a future enhancement. It can be accomplished by adding more medicine compartments and electronic components to the existing design.
•	Phone call notifications may have to be a future enhancement. There are fee based services such as “Phone Notify!” (www.cdyne.com) available which can be integrated into the solution.


### Product Materials and Costs
•	Tower Pro SG92R Micro Servo (2): $10 - used for the motor mechanism to dispense pills

•	ESP 8266 Transceiver Module: $5 – required for Wi-Fi connectivity

•	Arduino/Raspberry Pi Kits: $20 - $35 – electronic circuitry to interface with the dispenser and the web site

•	Speaker: $2 – for alerting

•	LED Lights: $2 – for alerting

•	Switches: $2 – for dispensing

•	Miscellaneous Items (battery, casing, wires, electronic components etc.): $10

      
## Implementation Time

 
•	February 6: Complete Medication Adherence research

•	February 7: Incorporate mentor and teacher feedback and submit project proposal

•	February 19: Work with Mr. McConnell on product design

•	February 26: Review final design and set up schedule with Mr. McConnell for building product

•	March 4: Order materials for building product

•	March 11 -18 (Spring break): Build and test product

•	April 29: Perform final product testing. Complete research and presentation

•	May 2: Test drive presentation with Mr. McConnell.

 


 

## Project Importance
 The area of Medication Adherence is one of growing concern. Many studies have brought to light the extremely damaging effects of non-adherence which include higher cost of health care, patient discomfort, and shorter lifespans. The solution arising from my project is expected to benefit a large section of the elderly population of our society given that they are most impacted by the problem. The project will serve to demonstrate how modern technology can be leveraged to develop solutions that can vastly improve the quality of life in society. Older people do not like visiting the hospital frequently and prefer options for home based health care. Family members find themselves under extreme duress when their loved ones are unhappy and uncomfortable especially because of a problem that is easily avoidable through proper discipline.  Health care professionals are at a disadvantage when they cannot accurately see the results of their treatment because of medication non-adherence. In the U.S. about 125,000 deaths and $100-$289 billion in costs per year are attributed to medication non-adherence (Dudzinski 2). The Smart Medicine Dispenser is a solution that will immensely help in tackling this serious problem. It will help instill much needed discipline in medicine taking.  By helping patients and their family members improve medication adherence, health care providers will find that they can be more effective in treating their patients.  The importance of the solution is far reaching. By bringing the Smart Medicine Dispenser solution into their lives, patients will not only help themselves but will also help their loved ones and care givers. 
 
## Works Cited
Arduino. “Arduino - Introduction.” https://www.arduino.cc/en/Guide/Introduction. Arduino, 2015. Web. 15 Dec. 2015.
Brown, Marie T., MD, and Jennifer K. Bussell, MD. "Medication Adherence: WHO Cares?”  Mayo Clinic Proceedings. Mayo Clinic, Apr. 2011. Web. 8 Dec. 2015.
Dudzinski, Kathryn. "Speaking to Patients about Medication Adherence." michiganpharmacists.org. Michigan Pharmacists Association, 2015. Web. 8 Dec. 2015.
Gottlieb Harold, PhD. "Medication Nonadherence: Finding Solutions to a Costly Medical Problem." Medscape.com. Cliggott Publishing, Division of CMP Healthcare Media, 2000. Web. 8 Dec. 2015.
Lamp, Amy. "The Value of Balancing Desirability, Feasibility, and Viability." forty.co/value-balancing-desirability-feasibility-viability. Forty, 22 Feb. 2014. Web. 9 Dec. 2015.
Mitchell, Alex J., and Thomas Selmes. "Why Don't Patients Take Their Medicine? Reasons and    Solutions in Psychiatry.” Advances in Psychiatric Treatment. Researchgate, Sept. 2007. Web. 8 Dec. 2015.
Morimoto, T, T K Gandhi, A C Seger, T C Hsieh, D W Bates "Adverse drug events and medication errors: detection and classification methods." Quality and safety in health care 13.4 (2004): 306-314. Pub Med Center (PMC).
Sabaté, Eduardo. "Adherence to Long-term Therapies: Evidence for Action." https://apps.who.int/iris/bitstream/10665/42682/1/9241545992.pdf. World Health Organization, 2003. Web. 14 Dec. 2015.
Swan, Melanie. "Sensor Mania! The Internet of Things, Wearable Computing, Objective Metrics, and the Quantified Self 2.0." JSAN Journal of Sensor and Actuator Networks 1.3. Multidisciplinary Digital Publishing Institute, 2012. Web. 9 Dec. 2015.
 
