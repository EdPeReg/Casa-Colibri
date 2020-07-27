# Casa-Colibri
This is a project made to help an organization CASA COLIBRÍ, as well to the subject "Ingenieria en computacion".

Coders:
<ul>
  <li> LUIS FRANCISCO GARCIA HIRSCHBERG </li>
  <li> ALAN SANDONVAL </li>
  <li> KARINA VILLA CISNEROS </li>
  <li> EDUARDO PEREZ REGIN </li>
  <li> CESAR JAVIER REYES AGUIRRE </li>

This software is intended to help the ONG Casa Colibrí, they need a better way to manage who are the kids that go 
to that organization, having some information about them.

All the information is stored in files (local way) using .json

FEATURES.

- Login Page:
  - Able to login depending of the user, for now there is only one user: admin pass:admin
  - Pop an error mesage in case the user doesn't exist.
- Perfiles:
  - "Actualizar perfiles": Will update the kids' profile once the button is hitten.
  - "Agregar": Will add a new profile to the file.
  - "Visor de perfiles: This option is activated if you click on a kid in the list, allows you to show his/her information, 
     to delete this profile and to put a picture to identify the kid.
  - "Eliminar perfil": Will delete the kids information.
- Estados de Animo:
  - Adds how the kid is feeling in that day, asking him one question "How do you feel today?", also be able to give 
    details.
  - Show the kids mood.
- Asistencia:
  - Able to take attendance in an easy way.
  - Able to see the attendance, you can see the attendance of each kid depending on the day selected on the calendar.
- Sueños:
  - Be able to introduce the kid dreams, adding the dream title and details.
  
NOTES:
  - Perfiles:
    - All the fields are free, you can write any information there, recommendation; validate those fields.
    - It doesn't show the kids list dinamically once you hit the button "Agregar"; it would be better to show it dinamically.
    - There is no way identify a particular kid, there is not an id.
    - When you delete a kid, it doesn't update the list dinamically.
    - To add a new profile, you must have at least the fields "Nombres" and "apellidos", if one of them are missing, it won't
      add the profile, it doesn't show anything; it would be better to pop a message.
 - Estados de Animo:
    - If you add a new profile, the list won't update until you hit "Actualizar perfiles"; it would be better to 
      show it dinamically.
    - You can enter whatever you want into the fields, find a way to validate correct information.
    - It only shows the last mood, not able to show different moods depending on the day.
  - Asistencia:
    - If you add a new profile, the list won't update until you hit "Actualizar perfiles"; it would be better to 
      show it dinamically.
    - You can edit the table when you are showing the attendance, any modification to that table is not reflected, if it
      doesn't reflect any modification, not be able to modify the values in the first place.
  - Sueños:
    - The fields are open, find a way to valide them.
    - It only show the dream from the current day, not other days.
